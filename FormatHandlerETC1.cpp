#include "FormatHandlerETC1.h"
#include <cstdio>
#include <cstdlib>

// note: this table and the mapping to the index table is REALLY confusingly laid out in the spec.
int FormatHandlerETC1::ms_modifierTable[8][4] = {
	{  2,   8,  -2,   -8,},
	{  5,  17,  -5,  -17,},
	{  9,  29,  -9,  -29,},
	{ 13,  42, -13,  -42,},
	{ 18,  60, -18,  -60,},
	{ 24,  80, -24,  -80,},
	{ 33, 106, -33, -106,},
	{ 47, 183, -47, -183,},
};

void FormatHandlerETC1::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 8;

	rgb_t* dstRgb = reinterpret_cast<rgb_t*>(dst);

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int blockX = (blockIndex % (width / getBlockWidth())) * getBlockWidth();
		int blockY = (blockIndex / (width / getBlockWidth())) * getBlockHeight();

		uint64_t block = readU64BE(&src);
		bool diffbit = (block >> 33) & 0x1;

		rgb_t baseCol[2];
		if (diffbit) {
			uint8_t r1 = ((block >> 59) & 0x1F);
			uint8_t g1 = ((block >> 51) & 0x1F);
			uint8_t b1 = ((block >> 43) & 0x1F);
			int8_t r2 = ((block >> 56) & 0x07);
			int8_t g2 = ((block >> 48) & 0x07);
			int8_t b2 = ((block >> 40) & 0x07);
			if (r2 & 0x4) r2 -= 8;
			if (g2 & 0x4) g2 -= 8;
			if (b2 & 0x4) b2 -= 8;
			baseCol[0] = rgb555torgb888(r1, g1, b1);
			baseCol[1] = rgb555torgb888(r1 + r2, g1 + g2, b1 + b2);
			// I'm not handling the potential underflow/overflow case on that addition,
			// because the spec says it's undefined behavior anyway.
		}
		else {
			uint8_t r1 = ((block >> 60) & 0xF);
			uint8_t r2 = ((block >> 56) & 0xF);
			uint8_t g1 = ((block >> 52) & 0xF);
			uint8_t g2 = ((block >> 48) & 0xF);
			uint8_t b1 = ((block >> 44) & 0xF);
			uint8_t b2 = ((block >> 40) & 0xF);
			baseCol[0] = rgb444torgb888(r1, g1, b1);
			baseCol[1] = rgb444torgb888(r2, g2, b2);
		}

		bool flipbit = (block >> 32) & 0x1;
		uint8_t tableCw[2];
		tableCw[0] = (block >> 37) & 0x7;
		tableCw[1] = (block >> 34) & 0x7;

		for (int i = 0; i < 16; i++) {
			uint8_t table = flipbit 
				? ((i & 2) ? 1 : 0)
				: ((i & 8) ? 1 : 0);

			int x = blockX + (i / getBlockWidth());
			int y = blockY + (i % getBlockWidth());

			rgb_t pixel = baseCol[table];
			uint8_t loBit = ((block >> i) & 1);
			uint8_t hiBit = ((block >> (i+16)) & 1);
			uint8_t index = loBit | (hiBit << 1);

			int modifier = ms_modifierTable[tableCw[table]][index];
			pixel.r = clamp(0, 255, (int)pixel.r + modifier);
			pixel.g = clamp(0, 255, (int)pixel.g + modifier);
			pixel.b = clamp(0, 255, (int)pixel.b + modifier);

			dstRgb[y*width+x] = pixel;
		}
	}
}

rgb_t FormatHandlerETC1::rgb444torgb888(uint8_t r, uint8_t g, uint8_t b) const {
	return rgb_t(
		r | (r << 4),
		g | (g << 4),
		b | (b << 4)
	);
}

rgb_t FormatHandlerETC1::rgb555torgb888(uint8_t r, uint8_t g, uint8_t b) const {
	return rgb_t(
		(r << 3) | (r >> 2),
		(g << 3) | (g >> 2),
		(b << 3) | (b >> 2)
	);
}

int FormatHandlerETC1::clamp(int min, int max, int a) const {
	return (a < min) ? min : (a > max) ? max : a;
}

std::string FormatHandlerETC1::getDescription() const { return "ETC1 compressed texture format"; }

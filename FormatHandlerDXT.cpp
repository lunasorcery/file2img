#include <cstdio>
#include <cstdlib>

#include "FormatHandlerDXT.h"

rgba_t FormatHandlerDXT::unpack565(uint16_t rgb565) {
	uint8_t r = (rgb565 >> 11) & 0x1F;
	uint8_t g = (rgb565 >>  5) & 0x3F;
	uint8_t b = (rgb565 >>  0) & 0x1F;
	return rgba_t(
		r << 3 | r >> 2,
		g << 2 | g >> 4,
		b << 3 | b >> 2,
		0xFF
	);
}

void FormatHandlerDXT::fillOutColorTable(uint16_t c0, uint16_t c1, rgba_t* colorTable) {
	colorTable[0] = unpack565(c0);
	colorTable[1] = unpack565(c1);
	if (c0 > c1) {
		colorTable[2] = rgba_t::lerp(colorTable[0], colorTable[1], 1.f / 3.f);
		colorTable[3] = rgba_t::lerp(colorTable[0], colorTable[1], 2.f / 3.f);
	} else {
		colorTable[2] = rgba_t::lerp(colorTable[0], colorTable[1], 0.5f);
		colorTable[3] = rgba_t(0, 0, 0, 0);
	}
}

void FormatHandlerDXT::fillOutAlphaTable(uint8_t a0, uint8_t a1, uint8_t* alphaTable) {
	alphaTable[0] = a0;
	alphaTable[1] = a1;
	if (a0 > a1) {
		alphaTable[2] = ((6 * a0) + a1) / 7;
		alphaTable[3] = ((5 * a0) + (2 * a1)) / 7;
		alphaTable[4] = ((4 * a0) + (3 * a1)) / 7;
		alphaTable[5] = ((3 * a0) + (4 * a1)) / 7;
		alphaTable[6] = ((2 * a0) + (5 * a1)) / 7;
		alphaTable[7] = (a0 + (6 * a1)) / 7;
	} else {
		alphaTable[2] = ((4 * a0) + a1) / 5;
		alphaTable[3] = ((3 * a0) + (2 * a1)) / 5;
		alphaTable[4] = ((2 * a0) + (3 * a1)) / 5;
		alphaTable[5] = (a0 + (4 * a1)) / 5;
		alphaTable[6] = 0;
		alphaTable[7] = 255;
	}
}

void FormatHandlerDXT1::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 8;

	rgba_t* dstRgba = reinterpret_cast<rgba_t*>(dst);

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int blockX = (blockIndex % (width / getBlockWidth())) * getBlockWidth();
		int blockY = (blockIndex / (width / getBlockWidth())) * getBlockHeight();

		uint16_t c0 = readU16LE(&src);
		uint16_t c1 = readU16LE(&src);
		uint32_t indexTable = readU32LE(&src);

		rgba_t colorTable[4];
		fillOutColorTable(c0, c1, colorTable);

		for (int i = 0; i < 16; ++i) {
			int x = blockX + (i % getBlockWidth());
			int y = blockY + (i / getBlockWidth());

			dstRgba[y * width + x] = colorTable[indexTable & 0x3];
			indexTable >>= 2;
		}
	}
}

void FormatHandlerDXT5::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 16;

	rgba_t* dstRgba = reinterpret_cast<rgba_t*>(dst);

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int blockX = (blockIndex % (width / getBlockWidth())) * getBlockWidth();
		int blockY = (blockIndex / (width / getBlockWidth())) * getBlockHeight();

		uint8_t a0 = readU8(&src);
		uint8_t a1 = readU8(&src);
		uint64_t alphaIndexTable = 0;
		for (int i = 0; i < 6; ++i) {
			alphaIndexTable <<= 8;
			alphaIndexTable |= readU8(&src);
		}
		
		uint16_t c0 = readU16LE(&src);
		uint16_t c1 = readU16LE(&src);
		uint32_t indexTable = readU32LE(&src);
		
		uint8_t alphaTable[8];
		rgba_t colorTable[4];
		fillOutAlphaTable(a0, a1, alphaTable);
		fillOutColorTable(c0, c1, colorTable);
		
		for (int i = 0; i < 16; ++i) {
			int x = blockX + (i % getBlockWidth());
			int y = blockY + (i / getBlockWidth());

			dstRgba[y*width+x] = rgba_t(
				colorTable[indexTable & 0x3].r,
				colorTable[indexTable & 0x3].g,
				colorTable[indexTable & 0x3].b,
				alphaTable[alphaIndexTable & 0x7]
			);

			indexTable >>= 2;
			alphaIndexTable >>= 3;
		}
	}
}

std::string FormatHandlerDXT1::getDescription() const { return "DXT1 compressed texture format"; }
std::string FormatHandlerDXT5::getDescription() const { return "DXT5 compressed texture format"; }

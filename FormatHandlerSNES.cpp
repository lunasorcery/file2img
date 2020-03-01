#include "FormatHandlerSNES.h"
#include <cstring>

// based on documentation from http://fdwr.tripod.com/docs/snesgfx.txt

void FormatHandlerSNES4bpp::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 32;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		uint8_t blockData[32];
		memcpy(blockData, src, 32);
		src += 32;
		int blockX = (blockIndex % (width / getBlockWidth())) * getBlockWidth();
		int blockY = (blockIndex / (width / getBlockWidth())) * getBlockHeight();
		for (int iy = 0; iy < 8; ++iy) {
			uint8_t bit0 = blockData[iy*2];
			uint8_t bit1 = blockData[iy*2+1];
			uint8_t bit2 = blockData[16+iy*2];
			uint8_t bit3 = blockData[16+iy*2+1];
			for (int ix = 0; ix < 8; ++ix) {
				uint8_t val = 0;
				val |= (((bit0>>(7-ix))&1)<<0);
				val |= (((bit1>>(7-ix))&1)<<1);
				val |= (((bit2>>(7-ix))&1)<<2);
				val |= (((bit3>>(7-ix))&1)<<3);
				val |= val << 4;
				int x = blockX + ix;
				int y = blockY + iy;
				dst[y*width+x] = val;
			}
		}
	}
}

std::string FormatHandlerSNES4bpp::getDescription() const { return "SNES 4bit bitplane"; }

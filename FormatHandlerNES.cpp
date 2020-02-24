#include <cstring>
#include "FormatHandlerNES.h"

void FormatHandlerNES::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 16;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int blockX = (blockIndex % (width / getBlockWidth())) * getBlockWidth();
		int blockY = (blockIndex / (width / getBlockWidth())) * getBlockHeight();
		uint8_t loBits[8];
		uint8_t hiBits[8];
		memcpy(loBits, src, 8); src += 8;
		memcpy(hiBits, src, 8); src += 8;
		for (int iy = 0; iy < 8; ++iy) {
			for (int ix = 0; ix < 8; ++ix) {
				uint8_t val = ((loBits[iy]>>(7-ix))&1) | (((hiBits[iy]>>(7-ix))&1)<<1);
				val |= val << 2;
				val |= val << 4;
				int x = blockX + ix;
				int y = blockY + iy;
				dst[y*width+x] = val;
			}
		}
	}
}

std::string FormatHandlerNES::getDescription() const { return "NES compressed tile format (grayscale)"; }

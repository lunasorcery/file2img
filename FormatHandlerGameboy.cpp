#include "FormatHandlerGameboy.h"

void FormatHandlerGameboy::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 16;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int blockX = (blockIndex % (width / getBlockWidth())) * getBlockWidth();
		int blockY = (blockIndex / (width / getBlockWidth())) * getBlockHeight();
		for (int iy = 0; iy < 8; ++iy) {
			uint8_t loBit = readU8(&src);
			uint8_t hiBit = readU8(&src);
			for (int ix = 0; ix < 8; ++ix) {
				uint8_t val = ((loBit>>(7-ix))&1) | (((hiBit>>(7-ix))&1)<<1);
				val |= val << 2;
				val |= val << 4;
				int x = blockX + ix;
				int y = blockY + iy;
				dst[y*width+x] = val;
			}
		}
	}
}

std::string FormatHandlerGameboy::getDescription() const { return "Gameboy compressed tile format (grayscale)"; }

#include <string.h>
#include "blockFormatHandlers.h"
#include "colorUtils.h"

static rgba8888_t mix(rgba8888_t x, rgba8888_t y, int w0, int w1) {
	return (rgba8888_t){
		(uint8_t)((x.r*w0 + y.r*w1)/(w0+w1)),
		(uint8_t)((x.g*w0 + y.g*w1)/(w0+w1)),
		(uint8_t)((x.b*w0 + y.b*w1)/(w0+w1)),
		(uint8_t)((x.a*w0 + y.a*w1)/(w0+w1))
	};
};

static void populateDXTColorTable(uint16_t c0, uint16_t c1, rgba8888_t* colorTable) {
	colorTable[0] = convertRGB565(c0);
	colorTable[1] = convertRGB565(c1);
	if (c0 > c1) {
		colorTable[2] = mix(colorTable[0], colorTable[1], 2, 1);
		colorTable[3] = mix(colorTable[0], colorTable[1], 1, 2);
	} else {
		colorTable[2] = mix(colorTable[0], colorTable[1], 1, 1);
		colorTable[3] = (rgba8888_t){0,0,0,0};
	}
}

static void populateDXTAlphaTable(uint8_t a0, uint8_t a1, uint8_t* alphaTable) {
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

void blockFormatHandlerDXT1(rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes) {
	int blockCount = numBytes / 8;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int const blockX = (blockIndex % (dstWidth / 4)) * 4;
		int const blockY = (blockIndex / (dstWidth / 4)) * 4;

		uint16_t const c0 = readU16LE(&src);
		uint16_t const c1 = readU16LE(&src);
		uint32_t indexTable = readU32LE(&src);

		rgba8888_t colorTable[4];
		populateDXTColorTable(c0, c1, colorTable);

		for (int i = 0; i < 16; ++i) {
			int const x = blockX + (i % 4);
			int const y = blockY + (i / 4);

			dst[y * dstWidth + x] = colorTable[indexTable & 0x3];
			indexTable >>= 2;
		}
	}
}

void blockFormatHandlerDXT5(rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes) {
	int blockCount = numBytes / 16;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int const blockX = (blockIndex % (dstWidth / 4)) * 4;
		int const blockY = (blockIndex / (dstWidth / 4)) * 4;

		uint8_t const a0 = *src++;
		uint8_t const a1 = *src++;
		uint64_t alphaIndexTable = readU48LE(&src);

		uint16_t const c0 = readU16LE(&src);
		uint16_t const c1 = readU16LE(&src);
		uint32_t indexTable = readU32LE(&src);
		
		uint8_t alphaTable[8];
		rgba8888_t colorTable[4];
		populateDXTAlphaTable(a0, a1, alphaTable);
		populateDXTColorTable(c0, c1, colorTable);
		
		for (int i = 0; i < 16; ++i) {
			int const x = blockX + (i % 4);
			int const y = blockY + (i / 4);

			dst[y*dstWidth+x] = (rgba8888_t){
				colorTable[indexTable & 0x3].r,
				colorTable[indexTable & 0x3].g,
				colorTable[indexTable & 0x3].b,
				alphaTable[alphaIndexTable & 0x7]
			};

			indexTable >>= 2;
			alphaIndexTable >>= 3;
		}
	}
}

void blockFormatHandlerGameboy(rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes) {
	int const blockCount = numBytes / 16;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int const blockX = (blockIndex % (dstWidth / 8)) * 8;
		int const blockY = (blockIndex / (dstWidth / 8)) * 8;
		for (int iy = 0; iy < 8; ++iy) {
			uint8_t const loBit = *src++;
			uint8_t const hiBit = *src++;
			for (int ix = 0; ix < 8; ++ix) {
				uint8_t const val = expand2(((loBit>>(7-ix))&1) | (((hiBit>>(7-ix))&1)<<1));
				int const x = blockX + ix;
				int const y = blockY + iy;
				dst[y*dstWidth+x] = (rgba8888_t){val,val,val,0xff};
			}
		}
	}
}

void blockFormatHandlerNES(rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes) {
	int const blockCount = numBytes / 16;

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		int const blockX = (blockIndex % (dstWidth / 8)) * 8;
		int const blockY = (blockIndex / (dstWidth / 8)) * 8;
		uint8_t loBits[8];
		uint8_t hiBits[8];
		memcpy(loBits, src, 8); src += 8;
		memcpy(hiBits, src, 8); src += 8;
		for (int iy = 0; iy < 8; ++iy) {
			for (int ix = 0; ix < 8; ++ix) {
				uint8_t const val = expand2(((loBits[iy]>>(7-ix))&1) | (((hiBits[iy]>>(7-ix))&1)<<1));
				int const x = blockX + ix;
				int const y = blockY + iy;
				dst[y*dstWidth+x] = (rgba8888_t){val,val,val,0xff};
			}
		}
	}
}

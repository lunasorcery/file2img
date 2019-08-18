#include <cstdio>
#include <cstdlib>

#include "FormatHandlerPVRTC.h"

void FormatHandlerPVRTC::morton(uint32_t blockIndex, uint16_t& blockX, uint16_t& blockY)
{
	blockX = blockY = 0;
	for (int shift = 0; blockIndex; ++shift) {
		blockY |= (blockIndex & 1) << shift;
		blockIndex >>= 1;
		blockX |= (blockIndex & 1) << shift;
		blockIndex >>= 1;
	}
}

uint8_t FormatHandlerPVRTC::unpack3to8(uint8_t value)
{
	return (value << 5) | (value << 2) | (value >> 1);
}

uint8_t FormatHandlerPVRTC::unpack4to8(uint8_t value)
{
	return (value << 4) | (value);
}

uint8_t FormatHandlerPVRTC::unpack5to8(uint8_t value)
{
	return (value << 3) | (value >> 2);
}

rgba_t FormatHandlerPVRTC::unpackColorA(uint16_t value)
{
	rgba_t color;
	if (value & 0x8000)
	{
		uint8_t r = (value >> 10) & 0x1F;
		uint8_t g = (value >> 5) & 0x1F;
		uint8_t b = value & 0x1F;
		color.a = 0xff;
		color.r = unpack5to8(r);
		color.g = unpack5to8(g);
		color.b = unpack5to8(b);
	}
	else
	{
		uint8_t a = (value >> 12) & 0x7;
		uint8_t r = (value >> 8) & 0xF;
		uint8_t g = (value >> 4) & 0xF;
		uint8_t b = value & 0xF;
		color.a = unpack3to8(a);
		color.r = unpack4to8(r);
		color.g = unpack4to8(g);
		color.b = unpack4to8(b);
	}
	return color;
}

rgba_t FormatHandlerPVRTC::unpackColorB(uint16_t value)
{
	rgba_t color;
	if (value & 0x8000)
	{
		uint8_t r = (value >> 10) & 0x1F;
		uint8_t g = (value >> 5) & 0x1F;
		uint8_t b = (value >> 1) & 0xF;
		color.a = 0xff;
		color.r = unpack5to8(r);
		color.g = unpack5to8(g);
		color.b = unpack4to8(b);
	}
	else
	{
		uint8_t a = (value >> 12) & 0x7;
		uint8_t r = (value >> 8) & 0xF;
		uint8_t g = (value >> 4) & 0xF;
		uint8_t b = (value >> 1) & 0x7;
		color.a = unpack3to8(a);
		color.r = unpack4to8(r);
		color.g = unpack4to8(g);
		color.b = unpack3to8(b);
	}
	return color;
}

void FormatHandlerPVRTC_4bpp_RGB::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	int blockCount = srcLength / 8;

	int blocksWide = (width / getBlockWidth());
	int blocksHigh = (blockCount / blocksWide);

	const uint8_t* srcStart = src;
	rgba_t* dstRgba = reinterpret_cast<rgba_t*>(dst);

	rgba_t* colorPlaneA = new rgba_t[blocksWide * blocksHigh];
	rgba_t* colorPlaneB = new rgba_t[blocksWide * blocksHigh];

	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		uint16_t blockX, blockY;
		morton(blockIndex, blockX, blockY);

		uint64_t blockWord = readU64LE(&src);
		rgba_t colorA = unpackColorA((uint16_t)(blockWord >> 48));
		rgba_t colorB = unpackColorB((uint16_t)(blockWord >> 32));
		colorPlaneA[blockY*blocksWide+blockX] = colorA;
		colorPlaneB[blockY*blocksWide+blockX] = colorB;
	}

	src = srcStart;
	for (int blockIndex = 0; blockIndex < blockCount; ++blockIndex) {
		uint16_t blockX, blockY;
		morton(blockIndex, blockX, blockY);

		uint64_t blockWord = readU64LE(&src);
		bool modeBit = (blockWord & 0x00010000) != 0;
		uint32_t modulationIndex = (uint32_t)(blockWord&0xFFFFFFFF);

		for (int i = 0; i < 16; ++i) {
			int ix = (i % getBlockWidth());
			int iy = (i / getBlockWidth());
			int x = blockX * getBlockWidth() + ix;
			int y = blockY * getBlockHeight() + iy;

			uint16_t blockX0 = (blockX-(ix<2?1:0))&(blocksWide-1);
			uint16_t blockY0 = (blockY-(iy<2?1:0))&(blocksHigh-1);
			uint16_t blockX1 = (blockX0+1)&(blocksWide-1);//(blockX+1)%blocksWide;
			uint16_t blockY1 = (blockY0+1)&(blocksHigh-1);//(blockY+1)%blocksWide;

			float wx = ((ix+2)%4)/(float)getBlockWidth();
			float wy = ((iy+2)%4)/(float)getBlockHeight();
			rgba_t colorA = rgba_t::lerp(
				rgba_t::lerp(
					colorPlaneA[blockY0*blocksWide+blockX0],
					colorPlaneA[blockY0*blocksWide+blockX1],
					wx
				),
				rgba_t::lerp(
					colorPlaneA[blockY1*blocksWide+blockX0],
					colorPlaneA[blockY1*blocksWide+blockX1],
					wx
				),
				wy
			);
			rgba_t colorB = rgba_t::lerp(
				rgba_t::lerp(
					colorPlaneB[blockY0*blocksWide+blockX0],
					colorPlaneB[blockY0*blocksWide+blockX1],
					wx
				),
				rgba_t::lerp(
					colorPlaneB[blockY1*blocksWide+blockX0],
					colorPlaneB[blockY1*blocksWide+blockX1],
					wx
				),
				wy
			);
			rgba_t modulationTable[4] = {
				colorB,
				modeBit ? rgba_t::lerp(colorB, colorA, 0.375f) : rgba_t::lerp(colorB, colorA, 0.5f),
				modeBit ? rgba_t::lerp(colorB, colorA, 0.625f) : rgba_t::lerp(colorB, colorA, 0.5f),
				colorA
			};
			dstRgba[y*width+x] = modulationTable[modulationIndex & 3];
			modulationIndex >>= 2;
		}
	}

	delete[] colorPlaneA;
	delete[] colorPlaneB;
}

std::string FormatHandlerPVRTC_4bpp_RGB::getDescription() const { return "PVRTC compressed texture format (4-bit, RGB)"; }

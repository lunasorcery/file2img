#include "FormatHandler565.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandler565::rgb565to8888(uint16_t rgb565, uint8_t* pr, uint8_t* pg, uint8_t* pb, uint8_t* pa) const {
	uint8_t r = (rgb565 >> 11) & 0x1F;
	uint8_t g = (rgb565 >>  5) & 0x3F;
	uint8_t b = (rgb565)       & 0x1F;
	*pr = r << 3 | r >> 2;
	*pg = g << 2 | g >> 4;
	*pb = b << 3 | b >> 2;
	*pa = 0xFF;
}

void FormatHandler565::bgr565to8888(uint16_t bgr565, uint8_t* pr, uint8_t* pg, uint8_t* pb, uint8_t* pa) const {
	uint8_t b = (bgr565 >> 11) & 0x1F;
	uint8_t g = (bgr565 >>  5) & 0x3F;
	uint8_t r = (bgr565)       & 0x1F;
	*pr = r << 3 | r >> 2;
	*pg = g << 2 | g >> 4;
	*pb = b << 3 | b >> 2;
	*pa = 0xFF;
}

void FormatHandlerRGB565BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	rgb565to8888(readU16BE(src), r, g, b, a);
}

void FormatHandlerRGB565LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	rgb565to8888(readU16LE(src), r, g, b, a);
}

void FormatHandlerBGR565BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	bgr565to8888(readU16BE(src), r, g, b, a);
}

void FormatHandlerBGR565LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	bgr565to8888(readU16LE(src), r, g, b, a);
}

std::string FormatHandlerRGB565BE::getDescription() const { return "RGB565 format, big-endian    (RRRRRGGG GGGBBBBB)"; }
std::string FormatHandlerRGB565LE::getDescription() const { return "RGB565 format, little-endian (GGGBBBBB RRRRRGGG)"; }
std::string FormatHandlerBGR565BE::getDescription() const { return "RGB565 format, big-endian    (BBBBBGGG GGGRRRRR)"; }
std::string FormatHandlerBGR565LE::getDescription() const { return "RGB565 format, little-endian (GGGRRRRR BBBBBGGG)"; }
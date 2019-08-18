#include "FormatHandlerARGB4444.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerARGB4444::argb4444to8888(uint16_t argb4444, uint8_t* pr, uint8_t* pg, uint8_t* pb, uint8_t* pa) const {
	uint8_t a = (argb4444 >> 12) & 0xF;
	uint8_t r = (argb4444 >>  8) & 0xF;
	uint8_t g = (argb4444 >>  4) & 0xF;
	uint8_t b = (argb4444 >>  0) & 0xF;
	*pr = r << 4 | r >> 4;
	*pg = g << 4 | g >> 4;
	*pb = b << 4 | b >> 4;
	*pa = a << 4 | a >> 4;
}

void FormatHandlerARGB4444BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	argb4444to8888(readU16BE(src), r, g, b, a);
}

void FormatHandlerARGB4444LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	argb4444to8888(readU16LE(src), r, g, b, a);
}

std::string FormatHandlerARGB4444BE::getDescription() const { return "ARGB4444 format big-endian    (AAAARRRR GGGGBBBB)"; }
std::string FormatHandlerARGB4444LE::getDescription() const { return "ARGB4444 format little-endian (GGGGBBBB AAAARRRR)"; }

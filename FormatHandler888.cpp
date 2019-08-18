#include "FormatHandler888.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerRGB888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*r = readU8(src);
	*g = readU8(src);
	*b = readU8(src);
	*a = 0xFF;
}

void FormatHandlerBGR888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*b = readU8(src);
	*g = readU8(src);
	*r = readU8(src);
	*a = 0xFF;
}

std::string FormatHandlerRGB888::getDescription() const { return "RGB888 format (RRRRRRRR GGGGGGGG BBBBBBBB)"; }
std::string FormatHandlerBGR888::getDescription() const { return "BGR888 format (BBBBBBBB GGGGGGGG RRRRRRRR)"; }
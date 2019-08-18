#include "FormatHandler8888.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerARGB8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*a = readU8(src);
	*r = readU8(src);
	*g = readU8(src);
	*b = readU8(src);
}

void FormatHandlerABGR8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*a = readU8(src);
	*b = readU8(src);
	*g = readU8(src);
	*r = readU8(src);
}

void FormatHandlerRGBA8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*r = readU8(src);
	*g = readU8(src);
	*b = readU8(src);
	*a = readU8(src);
}

void FormatHandlerBGRA8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*b = readU8(src);
	*g = readU8(src);
	*r = readU8(src);
	*a = readU8(src);
}

void FormatHandlerXRGB8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*a = 0xFF; readU8(src);
	*r = readU8(src);
	*g = readU8(src);
	*b = readU8(src);
}

void FormatHandlerXBGR8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*a = 0xFF; readU8(src);
	*b = readU8(src);
	*g = readU8(src);
	*r = readU8(src);
}

void FormatHandlerRGBX8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*r = readU8(src);
	*g = readU8(src);
	*b = readU8(src);
	*a = 0xFF; readU8(src);
}

void FormatHandlerBGRX8888::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	*b = readU8(src);
	*g = readU8(src);
	*r = readU8(src);
	*a = 0xFF; readU8(src);
}

std::string FormatHandlerARGB8888::getDescription() const { return "ARGB8888 format (AAAAAAAA RRRRRRRR GGGGGGGG BBBBBBBB)"; }
std::string FormatHandlerABGR8888::getDescription() const { return "ABGR8888 format (AAAAAAAA BBBBBBBB GGGGGGGG RRRRRRRR)"; }
std::string FormatHandlerRGBA8888::getDescription() const { return "RGBA8888 format (RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA)"; }
std::string FormatHandlerBGRA8888::getDescription() const { return "BGRA8888 format (BBBBBBBB GGGGGGGG RRRRRRRR AAAAAAAA)"; }
std::string FormatHandlerXRGB8888::getDescription() const { return "XRGB8888 format (no alpha) (XXXXXXXX RRRRRRRR GGGGGGGG BBBBBBBB)"; }
std::string FormatHandlerXBGR8888::getDescription() const { return "XBGR8888 format (no alpha) (XXXXXXXX BBBBBBBB GGGGGGGG RRRRRRRR)"; }
std::string FormatHandlerRGBX8888::getDescription() const { return "RGBX8888 format (no alpha) (RRRRRRRR GGGGGGGG BBBBBBBB XXXXXXXX)"; }
std::string FormatHandlerBGRX8888::getDescription() const { return "BGRX8888 format (no alpha) (BBBBBBBB GGGGGGGG RRRRRRRR XXXXXXXX)"; }
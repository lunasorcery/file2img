#include "FormatHandler1555.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandler1555::argb1555to8888(uint16_t argb1555, uint8_t* pr, uint8_t* pg, uint8_t* pb, uint8_t* pa) const {
	uint8_t a = (argb1555 & 0x8000) != 0 ? 0xFF : 0x00;
	uint8_t r = (argb1555 >> 10) & 0x1F;
	uint8_t g = (argb1555 >>  5) & 0x1F;
	uint8_t b = (argb1555)       & 0x1F;
	*pr = r << 3 | r >> 2;
	*pg = g << 3 | g >> 2;
	*pb = b << 3 | b >> 2;
	*pa = a;
}

void FormatHandler1555::abgr1555to8888(uint16_t abgr1555, uint8_t* pr, uint8_t* pg, uint8_t* pb, uint8_t* pa) const {
	uint8_t a = (abgr1555 & 0x8000) != 0 ? 0xFF : 0x00;
	uint8_t b = (abgr1555 >> 10) & 0x1F;
	uint8_t g = (abgr1555 >>  5) & 0x1F;
	uint8_t r = (abgr1555)       & 0x1F;
	*pr = r << 3 | r >> 2;
	*pg = g << 3 | g >> 2;
	*pb = b << 3 | b >> 2;
	*pa = a;
}

void FormatHandlerARGB1555BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	argb1555to8888(readU16BE(src), r, g, b, a);
}

void FormatHandlerARGB1555LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	argb1555to8888(readU16LE(src), r, g, b, a);
}

void FormatHandlerABGR1555BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	abgr1555to8888(readU16BE(src), r, g, b, a);
}

void FormatHandlerABGR1555LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	abgr1555to8888(readU16LE(src), r, g, b, a);
}

void FormatHandlerXRGB1555BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	argb1555to8888(readU16BE(src), r, g, b, a);
	*a = 0xFF;
}

void FormatHandlerXRGB1555LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	argb1555to8888(readU16LE(src), r, g, b, a);
	*a = 0xFF;
}

void FormatHandlerXBGR1555BE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	abgr1555to8888(readU16BE(src), r, g, b, a);
	*a = 0xFF;
}

void FormatHandlerXBGR1555LE::readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const {
	abgr1555to8888(readU16LE(src), r, g, b, a);
	*a = 0xFF;
}

std::string FormatHandlerARGB1555BE::getDescription() const { return "ARGB1555 format big-endian    (ARRRRRGG GGGBBBBB)"; }
std::string FormatHandlerARGB1555LE::getDescription() const { return "ARGB1555 format little-endian (GGGBBBBB ARRRRRGG)"; }
std::string FormatHandlerABGR1555BE::getDescription() const { return "ABGR1555 format big-endian    (ABBBBBGG GGGRRRRR)"; }
std::string FormatHandlerABGR1555LE::getDescription() const { return "ABGR1555 format little-endian (GGGRRRRR ABBBBBGG)"; }
std::string FormatHandlerXRGB1555BE::getDescription() const { return "XRGB1555 format big-endian    (no alpha) (XRRRRRGG GGGBBBBB)"; }
std::string FormatHandlerXRGB1555LE::getDescription() const { return "XRGB1555 format little-endian (no alpha) (GGGBBBBB XRRRRRGG)"; }
std::string FormatHandlerXBGR1555BE::getDescription() const { return "XBGR1555 format big-endian    (no alpha) (XBBBBBGG GGGRRRRR)"; }
std::string FormatHandlerXBGR1555LE::getDescription() const { return "XBGR1555 format little-endian (no alpha) (GGGRRRRR XBBBBBGG)"; }
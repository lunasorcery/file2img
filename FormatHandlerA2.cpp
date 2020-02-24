#include "FormatHandlerA2.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerA2BE::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	(void)width;
	for (int i = 0; i < srcLength; ++i) {
		for (int j = 0; j < 4; ++j) {
			uint8_t a = (src[i] << (j*2)) & 0xC0;
			a |= a >> 2;
			a |= a >> 4;
			*dst++ = a;
		}
	}
}

void FormatHandlerA2LE::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	(void)width;
	for (int i = 0; i < srcLength; ++i) {
		for (int j = 0; j < 4; ++j) {
			uint8_t a = (src[i] >> (j*2)) & 0x3;
			a |= a << 2;
			a |= a << 4;
			*dst++ = a;
		}
	}
}

std::string FormatHandlerA2BE::getDescription() const { return "2-bit gray format big-endian"; }

std::string FormatHandlerA2LE::getDescription() const { return "2-bit gray format little-endian"; }
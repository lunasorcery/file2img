#include "FormatHandlerA4.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerA4::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	(void)width;
	for (int i = 0; i < srcLength; ++i) {
		for (int j = 0; j < 2; ++j) {
			uint8_t a = (src[i] >> (j*4)) & 0xF;
			a |= a << 4;
			*dst++ = a;
		}
	}
}

std::string FormatHandlerA4::getDescription() const { return "4-bit gray format"; }

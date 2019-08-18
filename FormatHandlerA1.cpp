#include "FormatHandlerA1.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerA1::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	(void)width;
	for (int i = 0; i < srcLength; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (src[i]&(0x80>>j)) {
				*dst++ = 0xFF;
			}
			else {
				*dst++ = 0x00;
			}
		}
	}
}

std::string FormatHandlerA1::getDescription() const { return "1-bit gray format"; }

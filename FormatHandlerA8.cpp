#include "FormatHandlerA8.h"

#include <cstdio>
#include <cstdlib>
#include <string>

void FormatHandlerA8::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	(void)width;
	int pixelCount = pixelCountFromSrcLength(srcLength);
	memcpy(dst, src, pixelCount * getDstPixelComp());
}

std::string FormatHandlerA8::getDescription() const { return "8-bit gray format"; }

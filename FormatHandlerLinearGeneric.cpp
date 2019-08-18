#include "FormatHandlerLinearGeneric.h"

void FormatHandlerLinearGeneric::process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const {
	(void)width;
	int pixelCount = pixelCountFromSrcLength(srcLength);
	for (int i = 0; i < pixelCount; ++i) {
		uint8_t r, g, b, a;
		readPixel(&src, &r, &g, &b, &a);
		*dst++ = r;
		*dst++ = g;
		*dst++ = b;
		*dst++ = a;
	}
}

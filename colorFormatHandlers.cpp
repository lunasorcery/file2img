#include <cstring>
#include "colorFormatHandlers.h"
#include "colorUtils.h"

void colorFormatHandlerL1BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		for (int j = 0; j != 8; ++j) {
			uint8_t a = ((value<<j)&0x80) ? 0xff : 0x00;
			*dst++ = {a,a,a,0xff};
		}
	}
}

void colorFormatHandlerL1LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		for (int j = 0; j != 8; ++j) {
			uint8_t a = ((value>>j)&0x01) ? 0xff : 0x00;
			*dst++ = {a,a,a,0xff};
		}
	}
}

void colorFormatHandlerL2BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const a = expand2((value >> 6) & 0x3);
		uint8_t const b = expand2((value >> 4) & 0x3);
		uint8_t const c = expand2((value >> 2) & 0x3);
		uint8_t const d = expand2(value & 0x3);
		*dst++ = {a,a,a,0xff};
		*dst++ = {b,b,b,0xff};
		*dst++ = {c,c,c,0xff};
		*dst++ = {d,d,d,0xff};
	}
}

void colorFormatHandlerL2LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const a = expand2((value >> 6) & 0x3);
		uint8_t const b = expand2((value >> 4) & 0x3);
		uint8_t const c = expand2((value >> 2) & 0x3);
		uint8_t const d = expand2(value & 0x3);
		*dst++ = {d,d,d,0xff};
		*dst++ = {c,c,c,0xff};
		*dst++ = {b,b,b,0xff};
		*dst++ = {a,a,a,0xff};
	}
}

void colorFormatHandlerL4BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const hi = expand4(value >> 4);
		uint8_t const lo = expand4(value & 0xf);
		*dst++ = {hi,hi,hi,0xff};
		*dst++ = {lo,lo,lo,0xff};
	}
}

void colorFormatHandlerL4LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0;) {
		uint8_t const value = *src++;
		uint8_t const hi = expand4(value >> 4);
		uint8_t const lo = expand4(value & 0xf);
		*dst++ = {lo,lo,lo,0xff};
		*dst++ = {hi,hi,hi,0xff};
	}
}

void colorFormatHandlerL8(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	for (int i = numBytes; i-- != 0; ++dst, ++src) {
		*dst = {*src,*src,*src,0xff};
	}
}

void colorFormatHandlerRGB565BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertRGB565(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerRGB565LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertRGB565(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerBGR565BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertBGR565(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerBGR565LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertBGR565(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerARGB1555BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertARGB1555(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerARGB1555LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertARGB1555(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerABGR1555BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertABGR1555(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerABGR1555LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertABGR1555(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerXRGB1555BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertXRGB1555(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerXRGB1555LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertXRGB1555(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerXBGR1555BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertXBGR1555(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerXBGR1555LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertXBGR1555(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerARGB4444BE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertARGB4444(readU16BE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerARGB4444LE(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 2) {
		*dst++ = convertARGB4444(readU16LE(&src));
		numBytes -= 2;
	}
}

void colorFormatHandlerRGB888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 3) {
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		*dst++ = {r,g,b,0xff};
		numBytes -= 3;
	}
}

void colorFormatHandlerBGR888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 3) {
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		*dst++ = {r,g,b,0xff};
		numBytes -= 3;
	}
}

void colorFormatHandlerARGB8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const a = *src++;
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		*dst++ = {r,g,b,a};
		numBytes -= 4;
	}
}

void colorFormatHandlerABGR8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const a = *src++;
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		*dst++ = {r,g,b,a};
		numBytes -= 4;
	}
}

void colorFormatHandlerRGBA8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	// special case for this layout
	numBytes -= (numBytes % 4);
	memcpy(dst, src, numBytes);
}

void colorFormatHandlerBGRA8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		uint8_t const a = *src++;
		*dst++ = {r,g,b,a};
		numBytes -= 4;
	}
}

void colorFormatHandlerXRGB8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		++src; //uint8_t const x = *src++;
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		*dst++ = {r,g,b,0xff};
		numBytes -= 4;
	}
}

void colorFormatHandlerXBGR8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		++src; //uint8_t const x = *src++;
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		*dst++ = {r,g,b,0xff};
		numBytes -= 4;
	}
}

void colorFormatHandlerRGBX8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const r = *src++;
		uint8_t const g = *src++;
		uint8_t const b = *src++;
		++src; //uint8_t const x = *src++;
		*dst++ = {r,g,b,0xff};
		numBytes -= 4;
	}
}

void colorFormatHandlerBGRX8888(rgba8888_t* dst, uint8_t const* src, int numBytes) {
	while (numBytes >= 4) {
		uint8_t const b = *src++;
		uint8_t const g = *src++;
		uint8_t const r = *src++;
		++src; //uint8_t const x = *src++;
		*dst++ = {r,g,b,0xff};
		numBytes -= 4;
	}
}

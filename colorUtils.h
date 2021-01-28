#pragma once

#include "types.h"

inline uint8_t expand6(uint8_t a) { return (a << 2) | (a >> 4); }
inline uint8_t expand5(uint8_t a) { return (a << 3) | (a >> 2); }
inline uint8_t expand4(uint8_t a) { return (a << 4) | a; }
inline uint8_t expand2(uint8_t a) { return expand4((a << 2) | a); }

inline uint16_t readU16BE(uint8_t const** src) {
	uint16_t const hi = (*src)[0];
	uint16_t const lo = (*src)[1];
	*src += 2;
	return (hi<<8) | lo;
}

inline uint16_t readU16LE(uint8_t const** src) {
	uint16_t const lo = (*src)[0];
	uint16_t const hi = (*src)[1];
	*src += 2;
	return (hi<<8) | lo;
}

inline uint32_t readU32LE(uint8_t const** src) {
	uint32_t const a = (*src)[0];
	uint32_t const b = (*src)[1];
	uint32_t const c = (*src)[2];
	uint32_t const d = (*src)[3];
	*src += 4;
	return (d<<24) | (c<<16) | (b<<8) | a;
}

inline uint64_t readU48LE(uint8_t const** src) {
	uint64_t const a = (*src)[0];
	uint64_t const b = (*src)[1];
	uint64_t const c = (*src)[2];
	uint64_t const d = (*src)[3];
	uint64_t const e = (*src)[4];
	uint64_t const f = (*src)[5];
	*src += 6;
	return (f<<40) | (e<<32) | (d<<24) | (c<<16) | (b<<8) | a;
}

inline rgba8888_t convertRGB565(uint16_t value) {
	uint8_t const r = expand5(value >> 11);
	uint8_t const g = expand6((value >> 5) & 0x3f);
	uint8_t const b = expand5(value & 0x1f);
	return (rgba8888_t){r,g,b,0xff};
}

inline rgba8888_t convertBGR565(uint16_t value) {
	uint8_t const r = expand5(value & 0x1f);
	uint8_t const g = expand6((value >> 5) & 0x3f);
	uint8_t const b = expand5(value >> 11);
	return (rgba8888_t){r,g,b,0xff};
}

inline rgba8888_t convertARGB1555(uint16_t value) {
	uint8_t const a = (value & 0x8000) != 0 ? 0xff : 0x00;
	uint8_t const r = expand5((value >> 10) & 0x1f);
	uint8_t const g = expand5((value >> 5) & 0x1f);
	uint8_t const b = expand5(value & 0x1f);
	return (rgba8888_t){r,g,b,a};
}

inline rgba8888_t convertABGR1555(uint16_t value) {
	uint8_t const a = (value & 0x8000) != 0 ? 0xff : 0x00;
	uint8_t const r = expand5(value & 0x1f);
	uint8_t const g = expand5((value >> 5) & 0x1f);
	uint8_t const b = expand5((value >> 10) & 0x1f);
	return (rgba8888_t){r,g,b,a};
}

inline rgba8888_t convertXRGB1555(uint16_t value) {
	uint8_t const r = expand5((value >> 10) & 0x1f);
	uint8_t const g = expand5((value >> 5) & 0x1f);
	uint8_t const b = expand5(value & 0x1f);
	return (rgba8888_t){r,g,b,0xff};
}

inline rgba8888_t convertXBGR1555(uint16_t value) {
	uint8_t const r = expand5(value & 0x1f);
	uint8_t const g = expand5((value >> 5) & 0x1f);
	uint8_t const b = expand5((value >> 10) & 0x1f);
	return (rgba8888_t){r,g,b,0xff};
}

inline rgba8888_t convertARGB4444(uint16_t value) {
	uint8_t const a = expand4(value >> 12);
	uint8_t const r = expand4((value >> 8) & 0xf);
	uint8_t const g = expand4((value >> 4) & 0xf);
	uint8_t const b = expand4(value & 0xf);
	return (rgba8888_t){r,g,b,a};
}

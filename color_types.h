#pragma once

#include <cstdint>

struct rgb_t {
	uint8_t r, g, b;
	rgb_t();
	rgb_t(uint8_t r, uint8_t g, uint8_t b);
	static rgb_t lerp(const rgb_t& a, const rgb_t& b, float w);
};

struct rgba_t {
	uint8_t r, g, b, a;
	rgba_t();
	rgba_t(const rgb_t& rgb, uint8_t a);
	rgba_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	static rgba_t lerp(const rgba_t& a, const rgba_t& b, float w);
};

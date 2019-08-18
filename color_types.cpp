#include "color_types.h"

rgb_t::rgb_t() :
	r(0),
	g(0),
	b(0)
{ }

rgb_t::rgb_t(uint8_t r, uint8_t g, uint8_t b) :
	r(r),
	g(g),
	b(b)
{ }

rgb_t rgb_t::lerp(const rgb_t& a, const rgb_t& b, float w) {
	return rgb_t(
		a.r + (b.r - a.r) * w,
		a.g + (b.g - a.g) * w,
		a.b + (b.b - a.b) * w
	);
}

rgba_t::rgba_t() :
	r(0),
	g(0),
	b(0),
	a(0)
{ }

rgba_t::rgba_t(const rgb_t& rgb, uint8_t a) :
	r(rgb.r),
	g(rgb.g),
	b(rgb.b),
	a(a)
{ }

rgba_t::rgba_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
	r(r),
	g(g),
	b(b),
	a(a)
{ }

rgba_t rgba_t::lerp(const rgba_t& a, const rgba_t& b, float w) {
	return rgba_t(
		a.r + (b.r - a.r) * w,
		a.g + (b.g - a.g) * w,
		a.b + (b.b - a.b) * w,
		a.a + (b.a - a.a) * w
	);
}
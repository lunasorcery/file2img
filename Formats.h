#pragma once
#include <string>
#include "FormatHandler.h"

enum class eFormat {
	INVALID = -1,
	A1,
	A2,
	A4BE,
	A4LE,
	A8,
	ARGB8888,
	ABGR8888,
	RGBA8888,
	BGRA8888,
	XRGB8888,
	XBGR8888,
	RGBX8888,
	BGRX8888,
	RGB888,
	BGR888,
	RGB565BE,
	RGB565LE,
	BGR565BE,
	BGR565LE,
	ARGB1555BE,
	ARGB1555LE,
	ABGR1555BE,
	ABGR1555LE,
	XRGB1555BE,
	XRGB1555LE,
	XBGR1555BE,
	XBGR1555LE,
	ARGB4444BE,
	ARGB4444LE,
	dxt1,
	dxt5,
	etc1,
	pvrtc_4bpp_rgb,
	gameboy,
	nes,
	COUNT
};

std::string getNameFromFormat(eFormat format);
eFormat getFormatFromName(const std::string& name);
std::shared_ptr<FormatHandler> createFormatHandler(eFormat format);

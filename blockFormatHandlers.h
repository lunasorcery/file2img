#pragma once

#include "types.h"

void blockFormatHandlerDXT1    (rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
void blockFormatHandlerDXT5    (rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);

void blockFormatHandlerGameboy (rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
void blockFormatHandlerNES     (rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);

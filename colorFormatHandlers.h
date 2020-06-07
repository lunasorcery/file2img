#pragma once

#include "types.h"

void colorFormatHandlerL1BE       (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerL1LE       (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerL2BE       (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerL2LE       (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerL4BE       (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerL4LE       (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerL8         (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerRGB565BE   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerRGB565LE   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerBGR565BE   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerBGR565LE   (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerARGB4444BE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerARGB4444LE (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerARGB1555BE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerARGB1555LE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerABGR1555BE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerABGR1555LE (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerXRGB1555BE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerXRGB1555LE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerXBGR1555BE (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerXBGR1555LE (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerRGB888     (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerBGR888     (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerARGB8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerABGR8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerRGBA8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerBGRA8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);

void colorFormatHandlerXRGB8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerXBGR8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerRGBX8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);
void colorFormatHandlerBGRX8888   (rgba8888_t* dst, uint8_t const* src, int numBytes);

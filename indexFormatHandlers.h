#pragma once

#include "types.h"

void indexFormatHandlerI4BE (int* dst, uint8_t const* src, int numBytes);
void indexFormatHandlerI4LE (int* dst, uint8_t const* src, int numBytes);
void indexFormatHandlerI8   (int* dst, uint8_t const* src, int numBytes);

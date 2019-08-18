#pragma once

#include "FormatHandler.h"

class FormatHandlerLinearGeneric : public FormatHandler {
public:
	virtual int getBlockWidth() const override { return 1; } // for all linear formats, a block is just a pixel
	virtual int getBlockHeight() const override { return 1; }
	virtual int pixelCountFromSrcLength(int srcLength) const override = 0;
	virtual int getDstPixelComp() const override { return 4; }
	virtual int getPaletteStride() const override { return 0; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
protected:
	virtual void readPixel(const uint8_t**, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const = 0;
};

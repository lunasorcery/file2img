#include "FormatHandler.h"

class FormatHandlerA8 : public FormatHandler {
public:
	virtual std::string getDescription() const override;
	virtual int getBlockWidth() const override { return 1; }
	virtual int getBlockHeight() const override { return 1; }
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength; }
	virtual int getDstPixelComp() const override { return 1; }
	virtual int getPaletteStride() const override { return 1; } // do we allow this?
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

#include "FormatHandler.h"

class FormatHandlerA4 : public FormatHandler {
public:
	virtual std::string getDescription() const override;
	virtual int getBlockWidth() const override { return 1; }
	virtual int getBlockHeight() const override { return 1; }
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength * 2; }
	virtual int getDstPixelComp() const override { return 1; }
	virtual int getPaletteStride() const override { return 0; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

#include "FormatHandler.h"

class FormatHandlerNES : public FormatHandler {
public:
	virtual std::string getDescription() const override;
	virtual inline int getBlockWidth() const override final { return 8; }
	virtual inline int getBlockHeight() const override final { return 8; }
	virtual int getDstPixelComp() const override final { return 1; }
	virtual int pixelCountFromSrcLength(int srcLength) const override final { return (srcLength / 16) * 64; }
	virtual int getPaletteStride() const override { return 0; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override final;
};

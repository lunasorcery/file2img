#include "FormatHandler.h"

class FormatHandlerA4 : public FormatHandler {
public:
	virtual int getBlockWidth() const override { return 1; }
	virtual int getBlockHeight() const override { return 1; }
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength * 2; }
	virtual int getDstPixelComp() const override { return 1; }
	virtual int getPaletteStride() const override { return 0; }
};

class FormatHandlerA4BE : public FormatHandlerA4 {
public:
	virtual std::string getDescription() const override;
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

class FormatHandlerA4LE : public FormatHandlerA4 {
public:
	virtual std::string getDescription() const override;
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

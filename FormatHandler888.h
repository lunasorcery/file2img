#include "FormatHandlerLinearGeneric.h"

class FormatHandler888 : public FormatHandlerLinearGeneric {
public:
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength / 3; }
	virtual int getPaletteStride() const override { return 3; }
};

class FormatHandlerRGB888 : public FormatHandler888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerBGR888 : public FormatHandler888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

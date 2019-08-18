#include "FormatHandlerLinearGeneric.h"

class FormatHandler565 : public FormatHandlerLinearGeneric {
public:
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength / 2; }
	virtual int getPaletteStride() const override { return 2; }
protected:
	void rgb565to8888(uint16_t rgb565, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const;
	void bgr565to8888(uint16_t bgr565, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const;
};

class FormatHandlerRGB565BE : public FormatHandler565 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerRGB565LE : public FormatHandler565 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerBGR565BE : public FormatHandler565 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerBGR565LE : public FormatHandler565 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

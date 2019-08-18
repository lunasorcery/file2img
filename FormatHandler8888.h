#include "FormatHandlerLinearGeneric.h"

class FormatHandler8888 : public FormatHandlerLinearGeneric {
public:
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength / 4; }
	virtual int getPaletteStride() const override { return 4; }
};

class FormatHandlerARGB8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerABGR8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerRGBA8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerBGRA8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerXRGB8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerXBGR8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerRGBX8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerBGRX8888 : public FormatHandler8888 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

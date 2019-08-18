#include "FormatHandlerLinearGeneric.h"

class FormatHandlerARGB4444 : public FormatHandlerLinearGeneric {
public:
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength / 2; }
	virtual int getPaletteStride() const override { return 2; }
protected:
	void argb4444to8888(uint16_t argb4444, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const;
};

class FormatHandlerARGB4444BE : public FormatHandlerARGB4444 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerARGB4444LE : public FormatHandlerARGB4444 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

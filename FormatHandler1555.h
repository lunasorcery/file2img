#include "FormatHandlerLinearGeneric.h"

class FormatHandler1555 : public FormatHandlerLinearGeneric {
public:
	virtual int pixelCountFromSrcLength(int srcLength) const override { return srcLength / 2; }
	virtual int getPaletteStride() const override { return 2; }
protected:
	void argb1555to8888(uint16_t argb1555, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const;
	void abgr1555to8888(uint16_t abgr1555, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const;
};

class FormatHandlerARGB1555BE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerARGB1555LE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerABGR1555BE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerABGR1555LE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerXRGB1555BE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerXRGB1555LE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerXBGR1555BE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

class FormatHandlerXBGR1555LE : public FormatHandler1555 {
public:
	virtual std::string getDescription() const override;
	virtual void readPixel(const uint8_t** src, uint8_t* r, uint8_t* g, uint8_t* b, uint8_t* a) const override;
};

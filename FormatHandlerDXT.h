#include "FormatHandler.h"
#include "color_types.h"

class FormatHandlerDXT : public FormatHandler {
public:
	virtual int getBlockWidth() const override final { return 4; }
	virtual int getBlockHeight() const override final { return 4; }
	virtual int getDstPixelComp() const override final { return 4; }
	virtual int getPaletteStride() const override { return 0; }
protected:
	static rgba_t unpack565(uint16_t rgb565);
	static void fillOutColorTable(uint16_t c0, uint16_t c1, rgba_t* colorTable);
	static void fillOutAlphaTable(uint8_t a0, uint8_t a1, uint8_t* alphaTable);
};

class FormatHandlerDXT1 : public FormatHandlerDXT {
public:
	virtual std::string getDescription() const override;
	virtual int pixelCountFromSrcLength(int srcLength) const override { return (srcLength / 8) * 16; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

class FormatHandlerDXT5 : public FormatHandlerDXT {
public:
	virtual std::string getDescription() const override;
	virtual int pixelCountFromSrcLength(int srcLength) const override { return (srcLength / 16) * 16; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

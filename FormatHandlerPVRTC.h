#include "FormatHandler.h"
#include "color_types.h"

class FormatHandlerPVRTC : public FormatHandler {
public:
	virtual int getDstPixelComp() const override final { return 4; }
	virtual int getPaletteStride() const override { return 0; }
protected:
	static uint8_t unpack3to8(uint8_t value);
	static uint8_t unpack4to8(uint8_t value);
	static uint8_t unpack5to8(uint8_t value);
	static rgba_t unpackColorA(uint16_t value);
	static rgba_t unpackColorB(uint16_t value);
	static void morton(uint32_t blockIndex, uint16_t& blockX, uint16_t& blockY);
};

class FormatHandlerPVRTC_2bpp_RGB : public FormatHandlerPVRTC {
public:
	virtual std::string getDescription() const override;
	virtual int getBlockWidth() const override final { return 8; }
	virtual int getBlockHeight() const override final { return 4; }
	virtual int pixelCountFromSrcLength(int srcLength) const override { return (srcLength / 8) * 32; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};

class FormatHandlerPVRTC_4bpp_RGB : public FormatHandlerPVRTC {
public:
	virtual std::string getDescription() const override;
	virtual int getBlockWidth() const override final { return 4; }
	virtual int getBlockHeight() const override final { return 4; }
	virtual int pixelCountFromSrcLength(int srcLength) const override { return (srcLength / 8) * 16; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override;
};
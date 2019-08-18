#include "FormatHandler.h"
#include "color_types.h"

// https://www.khronos.org/registry/OpenGL/extensions/OES/OES_compressed_ETC1_RGB8_texture.txt

class FormatHandlerETC1 : public FormatHandler {
public:
	virtual std::string getDescription() const override;
	virtual inline int getBlockWidth() const override final { return 4; }
	virtual inline int getBlockHeight() const override final { return 4; }
	virtual int getDstPixelComp() const override final { return 3; }
	virtual int pixelCountFromSrcLength(int srcLength) const override final { return (srcLength / 8) * 16; }
	virtual int getPaletteStride() const override { return 0; }
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const override final;
private:
	rgb_t rgb444torgb888(uint8_t r, uint8_t g, uint8_t b) const;
	rgb_t rgb555torgb888(uint8_t r, uint8_t g, uint8_t b) const;
	int clamp(int min, int max, int a) const;
	static int ms_modifierTable[8][4];
};

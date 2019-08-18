#pragma once

#include <cstdint>
#include <string>

class FormatHandler {
public:
	virtual ~FormatHandler() = default;
	virtual std::string getDescription() const = 0;
	virtual int getBlockWidth() const = 0;
	virtual int getBlockHeight() const = 0;
	virtual int pixelCountFromSrcLength(int srcLength) const = 0;
	virtual int getDstPixelComp() const = 0;
	virtual int getPaletteStride() const = 0;
	virtual void process(const uint8_t* src, int srcLength, uint8_t* dst, int width) const = 0;
protected:
	static uint8_t readU8(const uint8_t** src);
	static uint16_t readU16BE(const uint8_t** src);
	static uint16_t readU16LE(const uint8_t** src);
	static uint32_t readU32BE(const uint8_t** src);
	static uint32_t readU32LE(const uint8_t** src);
	static uint64_t readU64BE(const uint8_t** src);
	static uint64_t readU64LE(const uint8_t** src);
};

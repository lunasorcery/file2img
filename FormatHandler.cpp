#include "FormatHandler.h"

#include <string>

uint8_t FormatHandler::readU8(const uint8_t** src) {
	uint8_t buf = **src;
	*src += 1;
	return buf;
}

uint16_t FormatHandler::readU16BE(const uint8_t** src) {
	uint8_t buf[sizeof(uint16_t)];
	memcpy(buf, *src, sizeof(uint16_t));
	*src += 2;
	return (buf[0] << 8) | buf[1];
}

uint16_t FormatHandler::readU16LE(const uint8_t** src) {
	uint8_t buf[sizeof(uint16_t)];
	memcpy(buf, *src, sizeof(uint16_t));
	*src += 2;
	return (buf[1] << 8) | buf[0];
}

uint32_t FormatHandler::readU32BE(const uint8_t** src) {
	uint8_t buf[sizeof(uint32_t)];
	memcpy(buf, *src, sizeof(uint32_t));
	*src += 4;
	return 
		(buf[0] << 24) | 
		(buf[1] << 16) | 
		(buf[2] << 8) | 
		buf[3];
}

uint32_t FormatHandler::readU32LE(const uint8_t** src) {
	uint8_t buf[sizeof(uint32_t)];
	memcpy(buf, *src, sizeof(uint32_t));
	*src += 4;
	return 
		(buf[3] << 24) | 
		(buf[2] << 16) | 
		(buf[1] << 8) | 
		(buf[0]);
}

uint64_t FormatHandler::readU64BE(const uint8_t** src) {
	uint8_t buf[sizeof(uint64_t)];
	memcpy(buf, *src, sizeof(uint64_t));
	*src += 8;
	return 
		((uint64_t)buf[0] << 56) | 
		((uint64_t)buf[1] << 48) | 
		((uint64_t)buf[2] << 40) | 
		((uint64_t)buf[3] << 32) | 
		((uint64_t)buf[4] << 24) | 
		((uint64_t)buf[5] << 16) | 
		((uint64_t)buf[6] << 8) | 
		((uint64_t)buf[7]);
}

uint64_t FormatHandler::readU64LE(const uint8_t** src) {
	uint8_t buf[sizeof(uint64_t)];
	memcpy(buf, *src, sizeof(uint64_t));
	*src += 8;
	return 
		((uint64_t)buf[7] << 56) | 
		((uint64_t)buf[6] << 48) | 
		((uint64_t)buf[5] << 40) | 
		((uint64_t)buf[4] << 32) | 
		((uint64_t)buf[3] << 24) | 
		((uint64_t)buf[2] << 16) | 
		((uint64_t)buf[1] << 8) | 
		((uint64_t)buf[0]);
}
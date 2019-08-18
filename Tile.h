#pragma once

#include <cstdint>

class Tile {
public:
	Tile() = delete;
	static void process(uint8_t* buffer, int comp, int width, int height, int tileWidth, int tileHeight);
};

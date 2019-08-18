#include <cstdio>
#include <cstdlib>
#include <string>
#include "Tile.h"

void Tile::process(uint8_t* buffer, int comp, int width, int height, int tileWidth, int tileHeight) {
	if ((width % tileWidth) != 0) {
		printf("Chosen layout must have a width divisible by %d.\n", tileWidth);
		exit(1);
	}
	if ((height % tileHeight) != 0) {
		printf("Chosen layout must have a height divisible by %d.\n", tileHeight);
		exit(1);
	}

	// TODO: we can be clever and do this with a scratch buffer that's only one tile till
	int numPixels = width * height;
	int bufferLength = numPixels * comp;
	uint8_t* scratch = new uint8_t[bufferLength];
	{
		for (int i = 0; i < numPixels; ++i) {
			int xinblock = i % tileWidth;
			int yinblock = (i / tileWidth) % tileHeight;
			int blockIndex = i / (tileWidth * tileHeight);
			int blockx = (blockIndex % (width /tileWidth)) * tileWidth;
			int blocky = (blockIndex / (width /tileWidth)) * tileHeight;
			int x = blockx + xinblock;
			int y = blocky + yinblock;
			int offset = y*width+x;
			memcpy(&scratch[offset*comp], &buffer[i*comp], (size_t)comp);
		}
		
		memcpy(buffer, scratch, (size_t)bufferLength);
	}
	delete[] scratch;
}
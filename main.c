#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "types.h"
#include "boilerplate.h"
#include "colorFormatHandlers.h"
#include "indexFormatHandlers.h"
#include "blockFormatHandlers.h"

typedef struct {
	char const* id;
	int bit_depth;
	void (*function)(int* dst, uint8_t const* src, int numBytes);
	char const* description;
} index_format_t;

typedef struct {
	char const* id;
	int bit_depth;
	void (*function)(rgba8888_t* dst, uint8_t const* src, int numBytes);
	char const* description;
} color_format_t;

typedef struct {
	char const* id;
	int bit_depth;
	int width;
	int height;
	void (*function)(rgba8888_t* dst, uint8_t const* src, int dstWidth, int numBytes);
	char const* description;
} block_format_t;


color_format_t all_color_formats[] = {
	{ .id="l1be",       .bit_depth= 1, .function=colorFormatHandlerL1BE,       .description="1-bit luminance format, big-endian (MSB first)", },
	{ .id="l1le",       .bit_depth= 1, .function=colorFormatHandlerL1LE,       .description="1-bit luminance format, little-endian (LSB first)", },
	{ .id="l2be",       .bit_depth= 2, .function=colorFormatHandlerL2BE,       .description="2-bit luminance format, big-endian (MSB first)", },
	{ .id="l2le",       .bit_depth= 2, .function=colorFormatHandlerL2LE,       .description="2-bit luminance format, little-endian (LSB first)", },
	{ .id="l4be",       .bit_depth= 4, .function=colorFormatHandlerL4BE,       .description="4-bit luminance format, big-endian (MSB first)", },
	{ .id="l4le",       .bit_depth= 4, .function=colorFormatHandlerL4LE,       .description="4-bit luminance format, little-endian (LSB first)", },
	{ .id="l8",         .bit_depth= 8, .function=colorFormatHandlerL8,         .description="8-bit luminance format", },

	{ .id="rgb565be",   .bit_depth=16, .function=colorFormatHandlerRGB565BE,   .description="RGB565 format, big-endian    (RRRRRGGG GGGBBBBB)", },
	{ .id="rgb565le",   .bit_depth=16, .function=colorFormatHandlerRGB565LE,   .description="RGB565 format, little-endian (GGGBBBBB RRRRRGGG)", },
	{ .id="bgr565be",   .bit_depth=16, .function=colorFormatHandlerBGR565BE,   .description="BGR565 format, big-endian    (BBBBBGGG GGGRRRRR)", },
	{ .id="bgr565le",   .bit_depth=16, .function=colorFormatHandlerBGR565LE,   .description="BGR565 format, little-endian (GGGRRRRR BBBBBGGG)", },
	
	{ .id="argb4444be", .bit_depth=16, .function=colorFormatHandlerARGB4444BE, .description="ARGB4444 format, big-endian    (AAAARRRR GGGGBBBB)", },
	{ .id="argb4444le", .bit_depth=16, .function=colorFormatHandlerARGB4444LE, .description="ARGB4444 format, little-endian (GGGGBBBB AAAARRRR)", },

	{ .id="argb1555be", .bit_depth=16, .function=colorFormatHandlerARGB1555BE, .description="ARGB1555 format, big-endian    (ARRRRRGG GGGBBBBB)", },
	{ .id="argb1555le", .bit_depth=16, .function=colorFormatHandlerARGB1555LE, .description="ARGB1555 format, little-endian (GGGBBBBB ARRRRRGG)", },
	{ .id="abgr1555be", .bit_depth=16, .function=colorFormatHandlerABGR1555BE, .description="ABGR1555 format, big-endian    (ABBBBBGG GGGRRRRR)", },
	{ .id="abgr1555le", .bit_depth=16, .function=colorFormatHandlerABGR1555LE, .description="ABGR1555 format, little-endian (GGGRRRRR ABBBBBGG)", },
	
	{ .id="xrgb1555be", .bit_depth=16, .function=colorFormatHandlerXRGB1555BE, .description="XRGB1555 format, big-endian    (no alpha) (XRRRRRGG GGGBBBBB)", },
	{ .id="xrgb1555le", .bit_depth=16, .function=colorFormatHandlerXRGB1555LE, .description="XRGB1555 format, little-endian (no alpha) (GGGBBBBB XRRRRRGG)", },
	{ .id="xbgr1555be", .bit_depth=16, .function=colorFormatHandlerXBGR1555BE, .description="XBGR1555 format, big-endian    (no alpha) (XBBBBBGG GGGRRRRR)", },
	{ .id="xbgr1555le", .bit_depth=16, .function=colorFormatHandlerXBGR1555LE, .description="XBGR1555 format, little-endian (no alpha) (GGGRRRRR XBBBBBGG)", },

	{ .id="rgb888",     .bit_depth=24, .function=colorFormatHandlerRGB888,     .description="RGB888 format (RRRRRRRR GGGGGGGG BBBBBBBB)" },
	{ .id="bgr888",     .bit_depth=24, .function=colorFormatHandlerBGR888,     .description="BGR888 format (BBBBBBBB GGGGGGGG RRRRRRRR)" },

	{ .id="argb8888",   .bit_depth=32, .function=colorFormatHandlerARGB8888,   .description="ARGB8888 format (AAAAAAAA RRRRRRRR GGGGGGGG BBBBBBBB)" },
	{ .id="abgr8888",   .bit_depth=32, .function=colorFormatHandlerABGR8888,   .description="ABGR8888 format (AAAAAAAA BBBBBBBB GGGGGGGG RRRRRRRR)" },
	{ .id="rgba8888",   .bit_depth=32, .function=colorFormatHandlerRGBA8888,   .description="RGBA8888 format (RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA)" },
	{ .id="bgra8888",   .bit_depth=32, .function=colorFormatHandlerBGRA8888,   .description="BGRA8888 format (BBBBBBBB GGGGGGGG RRRRRRRR AAAAAAAA)" },
	{ .id="xrgb8888",   .bit_depth=32, .function=colorFormatHandlerXRGB8888,   .description="XRGB8888 format (XXXXXXXX RRRRRRRR GGGGGGGG BBBBBBBB)" },
	{ .id="xbgr8888",   .bit_depth=32, .function=colorFormatHandlerXBGR8888,   .description="XBGR8888 format (XXXXXXXX BBBBBBBB GGGGGGGG RRRRRRRR)" },
	{ .id="rgbx8888",   .bit_depth=32, .function=colorFormatHandlerRGBX8888,   .description="RGBX8888 format (RRRRRRRR GGGGGGGG BBBBBBBB XXXXXXXX)" },
	{ .id="bgrx8888",   .bit_depth=32, .function=colorFormatHandlerBGRX8888,   .description="BGRX8888 format (BBBBBBBB GGGGGGGG RRRRRRRR XXXXXXXX)" },
};

index_format_t all_index_formats[] = {
	{ .id="i4be",       .bit_depth= 4, .function=indexFormatHandlerI4BE,       .description="4-bit index format, big-endian", },
	{ .id="i4le",       .bit_depth= 4, .function=indexFormatHandlerI4LE,       .description="4-bit index format, little-endian", },
	{ .id="i8",         .bit_depth= 8, .function=indexFormatHandlerI8,         .description="8-bit index format", },
};

block_format_t all_block_formats[] = {
	{ .id="dxt1",       .bit_depth= 64, .width=4, .height=4, .function=blockFormatHandlerDXT1,    .description="DXT1 block format", },
	{ .id="dxt5",       .bit_depth=128, .width=4, .height=4, .function=blockFormatHandlerDXT5,    .description="DXT5 block format", },

	{ .id="gameboy",    .bit_depth=128, .width=8, .height=8, .function=blockFormatHandlerGameboy, .description="Game Boy 2-bit tile format" },
	{ .id="nes",        .bit_depth=128, .width=8, .height=8, .function=blockFormatHandlerNES,     .description="NES 2-bit tile format" },
};

int const num_color_formats = array_size(all_color_formats);
int const num_index_formats = array_size(all_index_formats);
int const num_block_formats = array_size(all_block_formats);

index_format_t const* findIndexFormat(char const* id) {
	for (int i = 0; i < num_index_formats; ++i) {
		if (strEqualIgnoreCaseAssumeAscii(all_index_formats[i].id, id)) {
			return &all_index_formats[i];
		}
	}
	return NULL;
}

color_format_t const* findColorFormat(char const* id) {
	for (int i = 0; i < num_color_formats; ++i) {
		if (strEqualIgnoreCaseAssumeAscii(all_color_formats[i].id, id)) {
			return &all_color_formats[i];
		}
	}
	return NULL;
}

block_format_t const* findBlockFormat(char const* id) {
	for (int i = 0; i < num_block_formats; ++i) {
		if (strEqualIgnoreCaseAssumeAscii(all_block_formats[i].id, id)) {
			return &all_block_formats[i];
		}
	}
	return NULL;
}

color_format_t const* g_colorFormat = NULL;
block_format_t const* g_blockFormat = NULL;
index_format_t const* g_indexFormat = NULL;
int g_width = 256;
int g_tileWidth = 1;
int g_tileHeight = 1;
char const * g_outputPath = NULL;
int g_start = 0;
int g_paletteStart = 0;
int g_length = -1;

int g_argc;
char** g_argv;

void parseCommandLine() {
	while (1) {
		static struct option long_options[] = {
			{ "format",        required_argument, 0, 'f' },
			{ "list-formats",        no_argument, 0, 'F' },
			{ "tile",          required_argument, 0, 't' },
			{ "width",         required_argument, 0, 'w' },
			{ "output",        required_argument, 0, 'o' },
			{ "start",         required_argument, 0, 's' },
			{ "length",        required_argument, 0, 'n' },
			{ "index-format",  required_argument, 0, 'i' },
			{ "palette-start", required_argument, 0, 'p' },
			{ 0, 0, 0, 0 }
		};

		int option_index = 0;
		int c = getopt_long(g_argc, g_argv, "f:Ft:w:o:s:n:i:p:", long_options, &option_index);
		
		if (c == -1) {
			break;
		}

		switch (c) {
			case 'f': {
				char const* formatName = optarg;
				g_blockFormat = NULL;
				g_colorFormat = findColorFormat(formatName);
				if (!g_colorFormat) {
					g_blockFormat = findBlockFormat(formatName);
					if (!g_blockFormat) {
						eprintf("Unknown format specified: %s\n", formatName);
						exit(1);
					}
				}
				break;
			}
			case 'i': {
				char const* formatName = optarg;
				g_indexFormat = findIndexFormat(formatName);
				if (!g_indexFormat) {
					eprintf("Unknown index format specified: %s\n", formatName);
					exit(1);
				}
				break;
			}
			case 't': {
				// TODO: find an elegant way to get separate width/height
				g_tileHeight = g_tileWidth = strtol(optarg, NULL, 10);
				if (g_tileWidth <= 0) {
					eprintf("Tile size must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'w': {
				g_width = strtol(optarg, NULL, 10);
				if (g_width <= 0) {
					eprintf("Width must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'o': {
				g_outputPath = optarg;
				break;
			}
			case 's': {
				g_start = strtol(optarg, NULL, 10);
				if (g_start < 0) {
					eprintf("Start offset must be greater than or equal to zero.\n");
					exit(1);
				}
				break;
			}
			case 'p': {
				g_paletteStart = strtol(optarg, NULL, 10);
				if (g_start < 0) {
					eprintf("Palette start offset must be greater than or equal to zero.\n");
					exit(1);
				}
				break;
			}
			case 'n': {
				g_length = strtol(optarg, NULL, 10);
				if (g_length <= 0) {
					eprintf("Length must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'F': {
				printf("Available formats:\n");
				printf("- Color formats:\n");
				for (int i=0;i<num_color_formats;++i) {
					printf("  - %s\t\t(%s)\n", all_color_formats[i].id, all_color_formats[i].description);
				}
				printf("- Block formats:\n");
				for (int i=0;i<num_block_formats;++i) {
					printf("  - %s\t\t(%s)\n", all_block_formats[i].id, all_block_formats[i].description);
				}
				printf("- Index formats:\n");
				for (int i=0;i<num_index_formats;++i) {
					printf("  - %s\t\t(%s)\n", all_index_formats[i].id, all_index_formats[i].description);
				}
				exit(0);
			}
		}
	}
}

void earlySanityCheck() {
	if (optind >= g_argc) {
		puts("Usage:");
		puts("   file2img [options] <input file>");
		puts("");
		puts("Options:");
		puts("   -F,--list-formats    Print a list of available formats");
		puts("   -f,--format          Specify the color format (default: L8)");
		puts("   -t,--tile            Specify the tile size (default: 1/disabled)");
		puts("   -w,--width           Specify the target width (default: 256)");
		puts("   -o,--output          Specify the output path (default: out.png)");
		puts("   -s,--start           Specify the start offset (default: 0)");
		puts("   -n,--length          Specify the input byte count (default: all of them)");
		puts("   -i,--index-format    Specify the index map format (default: none)");
		puts("   -p,--palette-start   Specify the palette start offset (default: 0)");
		exit(0);
	}
	if (g_outputPath != NULL && optind + 1 < g_argc) {
		eprintf("Output path was specified along with multiple input files!\n");
		exit(1);
	}
	if (g_blockFormat && g_indexFormat) {
		eprintf("Cannot use block format %s as a palette source.\n", g_blockFormat->id);
		exit(1);
	}
	if (!g_colorFormat && !g_blockFormat && !g_indexFormat) {
		g_colorFormat = findColorFormat("l8");
	}
}

int calculatePixelCount(int numSrcBytes, color_format_t const* colorFormat, index_format_t const* indexFormat, block_format_t const* blockFormat)
{
	if (indexFormat) {
		return (numSrcBytes * 8) / indexFormat->bit_depth;
	} else if (blockFormat) {
		return (numSrcBytes * 8 * blockFormat->width * blockFormat->height) / blockFormat->bit_depth;
	} else {
		return (numSrcBytes * 8) / colorFormat->bit_depth;
	}
}

void applyTileLayout(rgba8888_t* buffer, int width, int height, int tileWidth, int tileHeight) {
	if ((width % tileWidth) != 0) {
		eprintf("Chosen layout must have a width divisible by %d.\n", tileWidth);
		exit(1);
	}
	if ((height % tileHeight) != 0) {
		eprintf("Chosen layout must have a height divisible by %d.\n", tileHeight);
		exit(1);
	}

	int const scratchPixelCount = width * tileHeight;
	int const numTileRows = height / tileHeight;
	rgba8888_t* scratch = NEW(rgba8888_t, scratchPixelCount);
	{
		for (int tileRow = 0; tileRow < numTileRows; ++tileRow) {
			for (int i = 0; i < scratchPixelCount; ++i) {
				int const xinblock = i % tileWidth;
				int const yinblock = (i / tileWidth) % tileHeight;
				int const blockIndex = i / (tileWidth * tileHeight);
				int const blockx = (blockIndex % (width /tileWidth)) * tileWidth;
				int const blocky = (blockIndex / (width /tileWidth)) * tileHeight;
				int const x = blockx + xinblock;
				int const y = blocky + yinblock;
				int const offset = y*width+x;
				scratch[offset] = buffer[i+tileRow*scratchPixelCount];
			}
			
			memcpy(buffer+tileRow*scratchPixelCount, scratch, (size_t)scratchPixelCount * sizeof(rgba8888_t));
		}
	}
	DELETE(scratch);
}

void processInputFile(char const* inputFilePath)
{
	FILE* fh = fopen(inputFilePath, "rb");
	{
		if (!fh) {
			eprintf("Failed to open %s\n", inputFilePath);
			return;
		}

		int srcLength = g_length;

		if (srcLength < 0) {
			// attempt to determine file length.
			// this will fail for things like /dev/random.
			fseek(fh, 0, SEEK_END);
			size_t const fileLength = ftell(fh);
			fseek(fh, 0, SEEK_SET);
			
			if (fileLength == 0) {
				eprintf("Failed to automatically determine length of '%s', or it's an empty file.\n", inputFilePath);
				eprintf("If this is some unbounded device like /dev/random, please specify an explicit length with -n\n");
				exit(1);
			}

			if (fileLength <= (size_t)g_start) {
				eprintf("Requested start position %d is beyond the end of the available data (%lu bytes).\n", g_start, fileLength);
				exit(1);
			}
			srcLength = (fileLength - g_start);
		}

		if (g_start != 0) {
			fseek(fh, g_start, SEEK_SET);
		}

		uint8_t* srcBuffer = NEW(uint8_t, srcLength);

		size_t const totalBytesRead = fread(srcBuffer, 1, srcLength, fh);
		if (totalBytesRead < (size_t)srcLength) {
			eprintf("Failed to read requested %d bytes, only %lu bytes were available.\n", srcLength, totalBytesRead);
			exit(1);
		}

		int const pixelCount = calculatePixelCount(srcLength, g_colorFormat, g_indexFormat, g_blockFormat);

		int width = g_width;
		int height = (pixelCount + width - 1) / width;

		if (g_blockFormat) {
			// ensure this width is valid
			if ((width % g_blockFormat->width) != 0) {
				eprintf("Requested block format %s requires a width divisible by %d.\n", g_blockFormat->id, g_blockFormat->width);
				exit(1);
			}

			// pad the height if necessary
			height = alignToMultiple(height, g_blockFormat->height);
		}

		// handle tile size
		if (g_tileWidth != 1 || g_tileHeight != 1) {
			if ((width % g_tileWidth) != 0) {
				eprintf("Width %d is not divisible by tile size %d.\n", width, g_tileWidth);
				exit(1);
			}
			if ((height % g_tileHeight) != 0) {
				if (g_blockFormat) {
					eprintf("Format %s is not trivially compatible with tile height %d.\n", g_blockFormat->id, g_tileHeight);
					exit(1);
				} else {
					height = alignToMultiple(height, g_tileHeight);
				}
			}
		}

		rgba8888_t* dstBuffer = NEW(rgba8888_t, width * height);
		memset(dstBuffer, 0, width * height * sizeof(rgba8888_t));
		int const dstComp = 4;

		if (g_indexFormat) {
			int const numPaletteEntries = (1 << g_indexFormat->bit_depth);
			int const paletteSizeBytes = (g_colorFormat->bit_depth * numPaletteEntries + 7) / 8;
			uint8_t* paletteSrcBuffer = NEW(uint8_t, paletteSizeBytes);
			
			fseek(fh, g_paletteStart, SEEK_SET);
			fread(paletteSrcBuffer, 1, paletteSizeBytes, fh);

			rgba8888_t palette[numPaletteEntries];
			g_colorFormat->function(palette, paletteSrcBuffer, paletteSizeBytes);
			
			int indexBuffer[width * height];
			g_indexFormat->function(indexBuffer, srcBuffer, srcLength);

			for (int i = 0; i != pixelCount; ++i) {
				dstBuffer[i] = palette[indexBuffer[i]];
			}

			DELETE(paletteSrcBuffer);
		} else if (g_blockFormat) {
			g_blockFormat->function(dstBuffer, srcBuffer, width, srcLength);
		} else {
			g_colorFormat->function(dstBuffer, srcBuffer, srcLength);
		}

		DELETE(srcBuffer);

		if (g_tileWidth != 1 || g_tileHeight != 1) {
			applyTileLayout(dstBuffer, width, height, g_tileWidth, g_tileHeight);
		}

		const char* filename = g_outputPath;
		if (filename == NULL) {
			filename = "out.png";
		}
		stbi_write_png(filename, width, height, dstComp, dstBuffer, width * dstComp);

		DELETE(dstBuffer);
	}
	fclose(fh);
}

int main(int argc, char** argv) {
	g_argc = argc;
	g_argv = argv;
	
	parseCommandLine();
	earlySanityCheck();

	for (int i = optind; i < g_argc; ++i) {
		eprintf("Processing file %s\n", g_argv[i]);
		processInputFile(g_argv[i]);
	}

	return 0;
}

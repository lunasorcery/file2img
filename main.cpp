#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <map>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "Formats.h"
#include "Tile.h"
#include "MathUtil.h"

eFormat g_format = eFormat::A8;
eFormat g_paletteFormat = eFormat::INVALID;
int g_width = 256;
int g_tileWidth = 1;
int g_tileHeight = 1;
const char* g_outputPath = nullptr;
int g_start = 0;
int g_paletteStart = 0;
int g_length = -1;
bool g_paletteZeroIsTransparent = false;

int g_argc;
char** g_argv;

void parseCommandLine() {
	while (1) {
		static struct option long_options[] = {
			{ "format",  required_argument, 0, 'f' },
			{ "list-formats",  no_argument, 0, 'F' },
			{ "tile",    required_argument, 0, 't' },
			{ "width",   required_argument, 0, 'w' },
			{ "output",  required_argument, 0, 'o' },
			{ "start",   required_argument, 0, 's' },
			{ "length",  required_argument, 0, 'n' },
			{ "palette-format", required_argument, 0, 'p' },
			{ "palette-start",  required_argument, 0, 'S' },
			{ "palette-zero-transparent",  no_argument, 0, 'z' },
			{ 0, 0, 0, 0 }
		};

		int option_index = 0;
		int c = getopt_long(g_argc, g_argv, "f:Ft:w:o:s:n:p:S:z", long_options, &option_index);
		
		if (c == -1) {
			break;
		}

		switch (c) {
			case 'f': {
				const char* formatName = optarg;
				g_format = getFormatFromName(formatName);
				if (g_format == eFormat::INVALID) {
					printf("Unknown format specified: %s\n", formatName);
					exit(1);
				}
				break;
			}
			case 'p': {
				const char* formatName = optarg;
				g_paletteFormat = getFormatFromName(formatName);
				if (g_paletteFormat == eFormat::INVALID) {
					printf("Unknown palette format specified: %s\n", formatName);
					exit(1);
				}
				break;
			}
			case 't': {
				// TODO: find an elegant way to get separate width/height
				g_tileHeight = g_tileWidth = strtol(optarg, nullptr, 10);
				if (g_tileWidth <= 0) {
					printf("Tile size must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'w': {
				g_width = strtol(optarg, nullptr, 10);
				if (g_width <= 0) {
					printf("Width must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'o': {
				g_outputPath = optarg;
				break;
			}
			case 's': {
				g_start = strtol(optarg, nullptr, 10);
				if (g_start < 0) {
					printf("Start offset must be greater than or equal to zero.\n");
					exit(1);
				}
				break;
			}
			case 'S': {
				g_paletteStart = strtol(optarg, nullptr, 10);
				if (g_start < 0) {
					printf("Palette start offset must be greater than or equal to zero.\n");
					exit(1);
				}
				break;
			}
			case 'n': {
				g_length = strtol(optarg, nullptr, 10);
				if (g_length <= 0) {
					printf("Length must be greater than zero.\n");
					exit(1);
				}
				break;
			}
			case 'F': {
				printf("Available formats:\n");
				for (uint32_t f = 0; f < (uint32_t)eFormat::COUNT; ++f)
				{
					eFormat format = (eFormat)f;
					printf(
						"%s: \033[20G%s\n",
						getNameFromFormat(format).c_str(),
						createFormatHandler(format)->getDescription().c_str()
					);
				}
				exit(0);
			}
			case 'z': {
				g_paletteZeroIsTransparent = true;
				break;
			}
		}
	}
}

void earlySanityCheck() {
	if (optind >= g_argc) {
		puts("Options:");
		puts("   -F,--list-formats   Print a list of available formats");
		puts("   -f,--format         Specify the pixel format (default: A8)");
		puts("   -t,--tile           Specify the tile size (default: 1/disabled)");
		puts("   -w,--width          Specify the target width (default: 256)");
		puts("   -o,--output         Specify the output path (default: out.png)");
		puts("   -s,--start          Specify the start offset (default: 0)");
		puts("   -n,--length         Specify the input byte count (default: all of them)");
		puts("   -p,--palette-format Specify the palette format (default: none)");
		puts("   -S,--palette-start  Specify the palette start offset (default: 0)");
		puts("   -z,--palette-zero-transparent  Force palette index zero to be transparent");
		exit(0);
	}
	if (g_outputPath != nullptr && optind + 1 < g_argc) {
		printf("Output path was specified along with multiple input files!\n");
		exit(1);
	}
}

void sanityCheckFormatPaletteCombination(
	std::shared_ptr<const FormatHandler> formatHandler,
	std::shared_ptr<const FormatHandler> paletteHandler)
{
	// if we don't have a palette handler then we're good
	if (paletteHandler == nullptr)
		return;

	// don't allow block handlers for palette pixel formats
	if (paletteHandler->getBlockWidth() != 1 || paletteHandler->getBlockHeight() != 1 || paletteHandler->getPaletteStride() == 0)
	{
		printf("Format %s cannot be used as a palette format.\n", getNameFromFormat(g_paletteFormat).c_str());
		exit(1);
	}

	if (formatHandler->getDstPixelComp() > 1)
	{
		printf("Format %s cannot be used as an index format.\n", getNameFromFormat(g_format).c_str());
		exit(1);
	}
}

void processInputFile(const char* infile)
{
	FILE* fh = fopen(infile, "rb");
	{
		if (!fh) {
			printf("Failed to open file %s\n", infile);
			return;
		}

		fseek(fh, 0, SEEK_END);
		size_t fileLength = ftell(fh);
		fseek(fh, 0, SEEK_SET);

		int srcLength = g_length;
		if (srcLength < 0) {
			// auto-detect data length
			srcLength = fileLength - g_start;
		}

		// start is greater than file length or file is empty
		if (srcLength <= 0) {
			printf("No data available!\n");
			exit(1);
		}

		if ((size_t)(g_start + srcLength) > fileLength) {
			printf("Requested more data than is available.\n");
			exit(1);
		}

		uint8_t* srcBuffer = new uint8_t[srcLength];
		if (srcLength > 0) {
			fseek(fh, g_start, SEEK_SET);
			fread(srcBuffer, 1, srcLength, fh);
		}

		std::shared_ptr<const FormatHandler> format = createFormatHandler(g_format);
		std::shared_ptr<const FormatHandler> paletteHandler = nullptr;
		if (g_paletteFormat != eFormat::INVALID) {
			paletteHandler = createFormatHandler(g_paletteFormat);
		}
		sanityCheckFormatPaletteCombination(format, paletteHandler);

		int pixelCount = format->pixelCountFromSrcLength(srcLength);

		int width = g_width;
		int height = (pixelCount + width - 1) / width;

		// ensure this width is valid for block formats
		if ((width % format->getBlockWidth()) != 0) {
			printf("Requested format %s requires a width divisible by %d.\n", getNameFromFormat(g_format).c_str(), format->getBlockWidth());
			exit(1);
		}

		// pad the height if necessary for block formats
		height = AlignToMultiple(height, format->getBlockHeight());

		// handle tile size
		if (g_tileWidth != 1 || g_tileHeight != 1)
		{
			if ((width % g_tileWidth) != 0)
			{
				printf("Width %d is not divisible by tile size %d.\n", width, g_tileWidth);
				exit(1);
			}
			if ((height % g_tileHeight) != 0)
			{
				if (format->getBlockHeight() == 1)
				{
					height = AlignToMultiple(height, g_tileHeight);
				}
				else
				{
					printf("Format %s is not trivially compatible with tile height %d.\n", getNameFromFormat(g_format).c_str(), g_tileHeight);
					exit(1);
				}
			}
		}

		int dstComp = format->getDstPixelComp();
		int dstLength = width * height * dstComp;
		uint8_t* dstBuffer = new uint8_t[dstLength];
		memset(dstBuffer, 0, dstLength);

		format->process(srcBuffer, srcLength, dstBuffer, width);

		if (g_tileWidth != 1 || g_tileHeight != 1)
		{
			Tile::process(dstBuffer, format->getDstPixelComp(), width, height, g_tileWidth, g_tileHeight);
		}

		if (paletteHandler != nullptr)
		{
			int paletteStride = paletteHandler->getPaletteStride();
			uint8_t* paletteSrcBuffer = new uint8_t[256 * paletteStride];
			fseek(fh, g_paletteStart, SEEK_SET);
			fread(paletteSrcBuffer, paletteStride, 256, fh);

			int paletteComp = paletteHandler->getDstPixelComp();
			uint8_t* dstBuffer2 = new uint8_t[width * height * paletteComp];
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					int index = dstBuffer[y*width*dstComp + x*dstComp];
					if (index == 0 && g_paletteZeroIsTransparent) {
						for (int i = 0; i < paletteComp; ++i) {
							dstBuffer2[y*width*paletteComp + x*paletteComp + i] = 0;
						}
					} else {
						paletteHandler->process(
							paletteSrcBuffer + (index*paletteStride),
							paletteStride,
							dstBuffer2 + y*width*paletteComp + x*paletteComp,
							1
						);
					}
				}
			}

			delete[] paletteSrcBuffer;

			// yucky hack
			dstComp = paletteComp;
			delete[] dstBuffer;
			dstBuffer = dstBuffer2;
		}

		const char* filename = g_outputPath;
		if (filename == nullptr) {
			filename = "out.png";
		}
		stbi_write_png(filename, width, height, dstComp, dstBuffer, width * dstComp);

		delete[] srcBuffer;
		delete[] dstBuffer;
	}
	fclose(fh);
}

int main(int argc, char** argv) {
	g_argc = argc;
	g_argv = argv;
	
	parseCommandLine();
	earlySanityCheck();

	for (int i = optind; i < g_argc; ++i) {
		printf("Processing file %s\n", g_argv[i]);
		processInputFile(g_argv[i]);
	}

	return 0;
}

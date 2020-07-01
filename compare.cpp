#include <cstdio>
#include <cstdint>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

struct rgba8888_t
{
	uint8_t r, g, b, a;
};

bool operator!=(rgba8888_t x, rgba8888_t y)
{
	return x.r!=y.r || x.g!=y.g || x.b!=y.b || x.a!=y.a;
}

struct image_t
{
	int width, height;
	rgba8888_t const* data;
	image_t(char const* filename)
	{
		int n;
		data = (rgba8888_t const*)stbi_load(filename, &width, &height, &n, 4);
	}
	~image_t()
	{
		if (data)
		{
			stbi_image_free((unsigned char*)data);
		}
	}
};

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		fprintf(stderr, "expected usage:\n");
		fprintf(stderr, "compare <test image path> <reference image path>\n");
		return 1;
	}

	char const* const pathTest = argv[1];
	char const* const pathRef = argv[2];

	image_t const imageTest(pathTest);

	if (!imageTest.data)
	{
		fprintf(stderr, "Failed to open test image %s\n", pathTest);
		return 1;
	}

	image_t const imageRef(pathRef);

	if (!imageRef.data)
	{
		fprintf(stderr, "Failed to open reference image %s\n", pathRef);
		return 1;
	}

	printf("Comparing '%s' against '%s':\n", pathTest, pathRef);

	if (imageTest.width != imageRef.width || imageTest.height != imageRef.height)
	{
		fprintf(stderr, "Mismatched image sizes!\n");
		fprintf(stderr, "Test image:       %d x %d\n", imageTest.width, imageTest.height);
		fprintf(stderr, "Reference image:  %d x %d\n", imageRef.width, imageRef.height);
		return 1;
	}

	rgba8888_t const* ptrTest = imageTest.data;
	rgba8888_t const* ptrRef = imageRef.data;
	for (int i = 0; i < imageTest.width * imageTest.height; ++i)
	{
		rgba8888_t const pixelTest = *ptrTest++;
		rgba8888_t const pixelRef = *ptrRef++;
		if (pixelTest != pixelRef)
		{
			int const x = i % imageTest.width;
			int const y = i / imageTest.width;
			fprintf(stderr, "Mismatched pixel at (%d, %d)\n", x, y);
			fprintf(stderr, "Test image:       rgba(%d, %d, %d, %d)\n", pixelTest.r, pixelTest.g, pixelTest.b, pixelTest.a);
			fprintf(stderr, "Reference image:  rgba(%d, %d, %d, %d)\n", pixelRef.r, pixelRef.g, pixelRef.b, pixelRef.a);
			return 1;
		}
	}

	printf("Images are identical!\n");

	return 0;
}

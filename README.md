# file2img

**file2img** is a small utility that can interpret any binary file as image data, in a variety of pixel formats. It's useful for looking at file contents in a visual manner, and for extracting usable images from arcane formats.


### Options:

```
file2img [options] <input file>

-F,--list-formats    Print a list of available formats
-f,--format          Specify the color format (default: L8)
-t,--tile            Specify the tile size (default: 1/disabled)
-w,--width           Specify the target width (default: 256)
-o,--output          Specify the output path (default: out.png)
-s,--start           Specify the start offset (default: 0)
-n,--length          Specify the input byte count (default: all of them)
-i,--index-format    Specify the index map format (default: none)
-p,--palette-start   Specify the palette start offset (default: 0)
```

### Example Usage:

Basic usage, outputs a 256-pixel-wide image mapping each input byte as one pixel:

```
file2img input.bin
```

Dumping a DXT5-compressed texture, with 65536 bytes of pixel data, starting at 128 bytes into the file, and saving it to `output.png`.

```
file2img -f dxt5 -n 65536 -s 128 input.dds -o output.png
```

Dumping a 32-pixel-wide paletted image, with a 1024-byte-long 8-bit index map at offset 0x200, and a little-endian XBGR1555 palette at offset 0x0.  
_Note: when dumping indexed/paletted images, `-f` specifies the color format of the palette, but `-s` specifies the start of the index map._

```
file2img -w 32 -n 1024 -i i8 -s $((0x200)) -f xbgr1555le -p $((0x0)) input.bin
```

Dumping an image with the pixels arranged in 8x8 tiles, rather than in conventional raster order:  
_Note: when dumping tiled images, the specified width must be a multiple of the tile size. The calculated height will be automatically padded as necessary._

```
file2img -t 8 input.bin
```

### Supported formats:

#### Color formats:
_These can only be used as inputs to the `-f` parameter._

* L1\* (1-bit luminance format)
* L2\* (2-bit luminance format)
* L4\* (4-bit luminance format)
* L8   (8-bit luminance format)
* RGB565\*
* BGR565\*
* ARGB4444\*
* ARGB1555\*
* ABGR1555\*
* XRGB1555\*
* XBGR1555\*
* RGB888
* BGR888
* ARGB8888
* ABGR8888
* RGBA8888
* BGRA8888
* XRGB8888
* XBGR8888
* RGBX8888
* BGRX8888

#### Block formats:
_These can only be used as inputs to the `-f` parameter, and only when `-i` isn't in use._

* DXT1       (DXT1 block format)
* DXT5       (DXT5 block format)
* GameBoy    (Game Boy 2-bit tile format)
* NES        (NES 2-bit tile format)

#### Index formats:
_These can only be used as inputs to the `-i` parameter._

* i4\*    (4-bit index format)
* i8      (8-bit index format)

\*: This supports big-endian and little-endian encodings with BE/LE suffixes.
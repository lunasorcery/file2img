# file2img

**file2img** is a small utility that can interpret any binary file as image data, in a variety of pixel formats. It's useful for looking at file contents in a visual manner, and for extracting usable images from arcane formats.


###Options:

```
-F,--list-formats    Print a list of available formats
-f,--format          Specify the pixel format (default: A8)
-t,--tile            Specify the tile size (default: 1/disabled)
-w,--width           Specify the target width (default: 256)
-o,--output          Specify the output path (default: out.png)
-s,--start           Specify the start offset (default: 0)
-n,--length          Specify the input byte count (default: all of them)
-p,--palette-format  Specify the palette color format (default: none)
-S,--palette-start   Specify the palette start offset (default: 0)
```

###Example Usage:

```
# DXT5-compressed image:
file2img -s 128 -n $((0x10000)) -f dxt5 input.dds

# paletted image, 8bit index map at 0x200, little-endian XBGR1555 palette at 0x0:
file2img -s $((0x200)) -n 1024 -w 32 -f A8 -p XBGR1555LE -S 0 something.bin
```

###Supported pixel formats:

* A1<sup>†</sup> (1-bit gray format)
* A2<sup>†</sup> (2-bit gray format)
* A4<sup>†</sup> (4-bit gray format)
* A8<sup>†</sup> (8-bit gray format)
* ARGB8888
* ABGR8888
* RGBA8888
* BGRA8888
* XRGB8888
* XBGR8888
* RGBX8888
* BGRX8888
* RGB888
* BGR888
* RGB565\*
* BGR565\*
* ARGB1555\*
* ABGR1555\*
* XRGB1555\*
* XBGR1555\*
* ARGB4444\*
* DXT1<sup>‡</sup>
* DXT5<sup>‡</sup>
* ETC1<sup>‡</sup>
* PVRTC 4bpp RGB<sup>‡</sup>
* Game Boy<sup>†‡</sup> (Game Boy compressed tile format, grayscale)
* NES<sup>†‡</sup> (NES compressed tile format, grayscale)

\*: This supports big-endian and little-endian encodings with BE/LE suffixes.  
<sup>†</sup>: This is a grayscale format that can be used as an index map for a palette.  
<sup>‡</sup>: This is a block-based format and cannot be used as a palette color format.  
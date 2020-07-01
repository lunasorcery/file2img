#!/bin/bash
mkdir -p test-data

# abort on failure
set -e



##### generate test images #####

# luminance formats
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl1le_w8_all-8bit-values.png  -f l1le  -w  8
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl1be_w8_all-8bit-values.png  -f l1be  -w  8
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl2le_w4_all-8bit-values.png  -f l2le  -w  4
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl2be_w4_all-8bit-values.png  -f l2be  -w  4
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl4le_w2_all-8bit-values.png  -f l4le  -w  2
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl4be_w2_all-8bit-values.png  -f l4be  -w  2
./file2img  reference-data/bin/all-8bit-values.bin  -o test-data/fl8_w16_all-8bit-values.png   -f l8    -w 16

# 565 formats
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/fbgr565be_w32_all-16bit-values.png  -f bgr565be  -w 32
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/fbgr565le_w32_all-16bit-values.png  -f bgr565le  -w 32
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/frgb565be_w32_all-16bit-values.png  -f rgb565be  -w 32
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/frgb565le_w32_all-16bit-values.png  -f rgb565le  -w 32

# 4444 formats
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/fargb4444be_w256_all-16bit-values.png  -f argb4444be  -w 256
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/fargb4444le_w256_all-16bit-values.png  -f argb4444le  -w 256

# 1555 formats
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/fabgr1555be_w32_all-16bit-values.png  -f abgr1555be  -w 32
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/fabgr1555le_w32_all-16bit-values.png  -f abgr1555le  -w 32
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/fargb1555be_w32_all-16bit-values.png  -f argb1555be  -w 32
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/fargb1555le_w32_all-16bit-values.png  -f argb1555le  -w 32
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/fxbgr1555be_w32_all-16bit-values.png  -f xbgr1555be  -w 32
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/fxbgr1555le_w32_all-16bit-values.png  -f xbgr1555le  -w 32
./file2img  reference-data/bin/all-16bit-be-values.bin  -o test-data/fxrgb1555be_w32_all-16bit-values.png  -f xrgb1555be  -w 32
./file2img  reference-data/bin/all-16bit-le-values.bin  -o test-data/fxrgb1555le_w32_all-16bit-values.png  -f xrgb1555le  -w 32



##### compare test images against reference images #####

# luminance formats
./compare  test-data/fl1le_w8_all-8bit-values.png  reference-data/img/fl1le_w8_all-8bit-values.png
./compare  test-data/fl1be_w8_all-8bit-values.png  reference-data/img/fl1be_w8_all-8bit-values.png
./compare  test-data/fl2le_w4_all-8bit-values.png  reference-data/img/fl2le_w4_all-8bit-values.png
./compare  test-data/fl2be_w4_all-8bit-values.png  reference-data/img/fl2be_w4_all-8bit-values.png
./compare  test-data/fl4le_w2_all-8bit-values.png  reference-data/img/fl4le_w2_all-8bit-values.png
./compare  test-data/fl4be_w2_all-8bit-values.png  reference-data/img/fl4be_w2_all-8bit-values.png
./compare  test-data/fl8_w16_all-8bit-values.png   reference-data/img/fl8_w16_all-8bit-values.png

# 565 formats
./compare  test-data/fbgr565be_w32_all-16bit-values.png  reference-data/img/fbgr565_w32_all-16bit-values.png
./compare  test-data/fbgr565le_w32_all-16bit-values.png  reference-data/img/fbgr565_w32_all-16bit-values.png
./compare  test-data/frgb565be_w32_all-16bit-values.png  reference-data/img/frgb565_w32_all-16bit-values.png
./compare  test-data/frgb565le_w32_all-16bit-values.png  reference-data/img/frgb565_w32_all-16bit-values.png

# 4444 formats
./compare  test-data/fargb4444be_w256_all-16bit-values.png  reference-data/img/fargb4444_w256_all-16bit-values.png
./compare  test-data/fargb4444le_w256_all-16bit-values.png  reference-data/img/fargb4444_w256_all-16bit-values.png

# 1555 formats
./compare  test-data/fabgr1555be_w32_all-16bit-values.png  reference-data/img/fabgr1555_w32_all-16bit-values.png
./compare  test-data/fabgr1555le_w32_all-16bit-values.png  reference-data/img/fabgr1555_w32_all-16bit-values.png
./compare  test-data/fargb1555be_w32_all-16bit-values.png  reference-data/img/fargb1555_w32_all-16bit-values.png
./compare  test-data/fargb1555le_w32_all-16bit-values.png  reference-data/img/fargb1555_w32_all-16bit-values.png
./compare  test-data/fxbgr1555be_w32_all-16bit-values.png  reference-data/img/fxbgr1555_w32_all-16bit-values.png
./compare  test-data/fxbgr1555le_w32_all-16bit-values.png  reference-data/img/fxbgr1555_w32_all-16bit-values.png
./compare  test-data/fxrgb1555be_w32_all-16bit-values.png  reference-data/img/fxrgb1555_w32_all-16bit-values.png
./compare  test-data/fxrgb1555le_w32_all-16bit-values.png  reference-data/img/fxrgb1555_w32_all-16bit-values.png

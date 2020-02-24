FILES = \
	main.cpp \
	color_types.cpp \
	FormatHandler.cpp \
	FormatHandler565.cpp \
	FormatHandler888.cpp \
	FormatHandler1555.cpp \
	FormatHandler8888.cpp \
	FormatHandlerA1.cpp \
	FormatHandlerA2.cpp \
	FormatHandlerA4.cpp \
	FormatHandlerA8.cpp \
	FormatHandlerARGB4444.cpp \
	FormatHandlerDXT.cpp \
	FormatHandlerETC1.cpp \
	FormatHandlerGameboy.cpp \
	FormatHandlerNES.cpp \
	FormatHandlerLinearGeneric.cpp \
	FormatHandlerPVRTC.cpp \
	Tile.cpp \
	MathUtil.cpp \
	Formats.cpp

HEADERS = \
	color_types.h \
	FormatHandler.h \
	FormatHandler565.h \
	FormatHandler888.h \
	FormatHandler1555.h \
	FormatHandler8888.h \
	FormatHandlerA1.h \
	FormatHandlerA2.h \
	FormatHandlerA4.h \
	FormatHandlerA8.h \
	FormatHandlerARGB4444.h \
	FormatHandlerDXT.h \
	FormatHandlerETC1.h \
	FormatHandlerGameboy.h \
	FormatHandlerNES.h \
	FormatHandlerLinearGeneric.h \
	FormatHandlerPVRTC.h \
	Tile.h \
	MathUtil.h \
	Formats.h \
	stb/stb_image_write.h

CXX ?= clang

all: file2img

file2img: $(FILES) $(HEADERS)
	$(CXX) $(FILES) -std=gnu++11 -lstdc++ -o file2img -Wall -Wextra -Werror -std=c++17 -O3

install: file2img
	cp file2img /usr/local/bin/file2img

uninstall:
	rm -f /usr/local/bin/file2img

clean:
	rm -f file2img

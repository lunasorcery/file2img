SOURCES = \
	main.cpp \
	blockFormatHandlers.cpp \
	colorFormatHandlers.cpp \
	indexFormatHandlers.cpp

HEADERS = \
	boilerplate.h \
	colorUtils.h \
	types.h \
	blockFormatHandlers.h \
	colorFormatHandlers.h \
	indexFormatHandlers.h \
	stb_image_write.h


CXX ?= clang

all: file2img

file2img: $(SOURCES) $(HEADERS)
	$(CXX) $(SOURCES) -std=c++2a -lstdc++ -o file2img -Wall -Wextra -O3

install: file2img
	cp file2img /usr/local/bin/file2img

uninstall:
	rm -f /usr/local/bin/file2img

clean:
	rm -f file2img

.PHONY: all install uninstall clean

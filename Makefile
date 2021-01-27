SOURCES = \
	main.c \
	blockFormatHandlers.c \
	colorFormatHandlers.c \
	indexFormatHandlers.c

HEADERS = \
	boilerplate.h \
	colorUtils.h \
	types.h \
	blockFormatHandlers.h \
	colorFormatHandlers.h \
	indexFormatHandlers.h \
	stb_image_write.h


CC ?= clang

all: file2img

file2img: $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) -std=c99 -lstdc++ -o file2img -Wall -Wextra -O3

install: file2img
	cp file2img /usr/local/bin/file2img

uninstall:
	rm -f /usr/local/bin/file2img

clean:
	rm -f file2img

.PHONY: all install uninstall clean

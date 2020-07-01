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
	stb/stb_image_write.h


CXX ?= clang

.PHONY: all test install uninstall clean

all: file2img

file2img: $(SOURCES) $(HEADERS)
	$(CXX) $(SOURCES) -std=c++2a -lstdc++ -o file2img -Wall -Wextra -O3

compare: compare.cpp stb/stb_image.h
	$(CXX) compare.cpp -o compare -Wall -Wextra -O3

test: file2img compare
	./test.sh

install: file2img
	cp file2img /usr/local/bin/file2img

uninstall:
	rm -f /usr/local/bin/file2img

clean:
	rm -f file2img
	rm -f compare
	rm -rf test-data

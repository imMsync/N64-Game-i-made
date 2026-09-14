V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: my_game.z64

clean:
	rm -rf $(BUILD_DIR) *.z64

.PHONY: all clean

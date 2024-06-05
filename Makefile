CC = g++
INCLUDES = -Iinclude \
	-Isrc/parser \
	-Isrc/scanner \
	-Isrc/std
CFLAGS = $(INCLUDES) -lm
DEBUG_FLAGS = -g -O0 -Wall -Wextra -save-temps -Wshadow -Wfloat-equal -Wundef -fsanitize=address
RELEASE_FLAGS = -O3

OUT_OBJ = minesweeper

BUILD = build
SOURCES = $(shell find . -name "*.cpp")

$(OUT_OBJ):
	mkdir -p $(BUILD)
	$(CC) $(RELEASE_FLAGS) $(SOURCES) -o $(BUILD)/$@ $(CFLAGS)
debug:
	mkdir -p $(BUILD)
	$(CC) $(DEBUG_FLAGS) $(SOURCES) -o $(BUILD)/$@ $(CFLAGS)

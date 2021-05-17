C = gcc

INC_DIR = include

OBJS = src/util.c src/tile.c src/minefield.c src/game.c src/main.c
COMPILER_FLAGS = -O3
DEBUG_FLAGS = -g -Wall -Wextra -Wfloat-equal -Wpedantic -fsanitize=address
OBJ_OUT = Minesweeper

all:
	$(C) $(OBJS) -I$(INC_DIR) $(COMPILER_FLAGS) $(DEBUG_FLAGS) -o $(OBJ_OUT)
release:
	$(C) $(OBJS) -I$(INC_DIR) $(COMPILER_FLAGS) -o $(OBJ_OUT)

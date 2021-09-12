CC = gcc
CFLAGS = -Iinclude -O3 -g -Wall -Wextra -Wfloat-equal -Wpedantic
LINKER_FLAGS = -fsanitize=address

SRC = $(wildcard src/*.c)
OBJ = $(subst .c,.o,$(SRC))

minesweeper: $(OBJ)
	$(CC) $(LINKER_FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm $(OBJ) minesweeper

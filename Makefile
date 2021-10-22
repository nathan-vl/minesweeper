CC = gcc
CFLAGS = -Iinclude -O3 -g -Wall -Wextra -Wfloat-equal -Wpedantic

SRC = $(wildcard src/*.c)
OBJS = $(subst .c,.o,$(SRC))

OUT_OBJ = minesweeper

$(OUT_OBJ): $(OBJS)
	$(CC) $^ -o $@

.PHONY: clean

clean:
	rm $(OBJS) $(OUT_OBJ)

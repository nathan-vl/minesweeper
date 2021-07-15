cc = gcc
include_dir = -Iinclude

compiler_flags = -O3
debug_flags = -g -Wall -Wextra -Wfloat-equal -Wpedantic -fsanitize=address

objects = $(wildcard src/*.c)

output_object = Minesweeper

debug:
	$(cc) $(include_dir) \
	$(compiler_flags) $(debug_flags) \
	$(objects) \
	-o $(output_object)

$(output_object):
	$(cc) $(include_dir) \
	$(compiler_flags) \
	$(objects) \
	-o $(output_object)

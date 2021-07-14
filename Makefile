cc = gcc
include_dir = -Iinclude

linker_flags = -lncurses
compiler_flags = -O3
debug_flags = -g -Wall -Wextra -Wfloat-equal -Wpedantic -fsanitize=address

objects = $(wildcard src/*.c)

output_object = Minesweeper

debug:
	$(cc) $(include_dir) \
	$(linker_flags) $(compiler_flags) $(debug_flags) \
	$(objects) \
	-o $(output_object)

$(output_object):
	$(cc) $(include_dir) \
	$(linker_flags) $(compiler_flags) \
	$(objects) \
	-o $(output_object)

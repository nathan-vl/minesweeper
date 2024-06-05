#pragma once

#include <cstddef>

typedef struct Pos
{
    std::size_t x;
    std::size_t y;
} Pos;

int randomInt(int min, int max);
bool isInBoundPos(Pos game_size, Pos pos);

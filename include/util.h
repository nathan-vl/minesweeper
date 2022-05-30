#ifndef UTIL_H
#define UTIL_H

typedef struct Pos
{
    size_t x;
    size_t y;
} Pos;

int randomInt(int min, int max);
_Bool isInBoundPos(Pos game_size, Pos pos);

#endif

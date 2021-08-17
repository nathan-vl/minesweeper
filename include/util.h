#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

struct Pos
{
    int x;
    int y;
};

int randomInt(const int min, const int max);
struct Pos newPos(int x, int y);
bool isInBound(struct Pos gameSize, struct Pos pos);

#endif

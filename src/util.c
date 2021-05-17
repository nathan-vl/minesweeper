#include "util.h"
#include <stdlib.h>

int randint(const int min, const int max)
{
    return ((double)rand() / RAND_MAX) * (max - min + 1) + min;
}

struct Pos newPos(int x, int y)
{
    struct Pos pos;
    pos.x = x;
    pos.y = y;

    return pos;
}

struct Pos randPos(const struct Pos max)
{
    int x = randint(0, max.x);
    int y = randint(0, max.y);

    return newPos(x, y);
}

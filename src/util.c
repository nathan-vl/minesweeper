#include "util.h"
#include <stdlib.h>

int randomInt(const int min, const int max)
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

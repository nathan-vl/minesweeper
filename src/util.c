#include <stdlib.h>
#include "util.h"

int random_int(const int min, const int max)
{
    return ((double)rand() / RAND_MAX) * (max - min + 1) + min;
}

_Bool is_in_bound(struct Pos game_size, struct Pos pos)
{
    return pos.x < game_size.x && pos.y < game_size.y;
}

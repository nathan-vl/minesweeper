#ifndef UTIL_H
#define UTIL_H

struct Pos
{
    int x;
    int y;
};

int random_int(const int min, const int max);
_Bool is_in_bound(struct Pos game_size, struct Pos pos);

#endif

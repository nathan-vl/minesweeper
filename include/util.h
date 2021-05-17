#ifndef UTIL
#define UTIL

struct Pos
{
    int x;
    int y;
};

int randint(const int min, const int max);
struct Pos newPos(int x, int y);
struct Pos randPos(const struct Pos max);

#endif

#ifndef UTIL_H
#define UTIL_H

struct Pos
{
    int x;
    int y;
};

int randomInt(const int min, const int max);
struct Pos newPos(int x, int y);

#endif

#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

enum TileStatus
{
    OPEN,
    FLAG,
    COVERED,
    GUESS
};

struct Tile
{
    bool hasMine;
    enum TileStatus status;
    int neighbours;
};

#endif

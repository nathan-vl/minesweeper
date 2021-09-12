#ifndef TILE_H
#define TILE_H

enum TileStatus
{
    OPEN,
    FLAG,
    COVERED,
    GUESS
};

struct Tile
{
    _Bool hasMine;
    enum TileStatus status;
    int neighbours;
};

#endif

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
    _Bool has_mine;
    enum TileStatus status;
    short neighbours;
};

#endif

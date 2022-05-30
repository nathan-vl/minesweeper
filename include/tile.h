#ifndef TILE_H
#define TILE_H

typedef enum TileStatus
{
    OPEN,
    FLAG,
    COVERED,
    GUESS
} TileStatus;

typedef struct Tiles
{
    _Bool *mines;
    short *neighbours;
    TileStatus *status;
} Tiles;

#endif

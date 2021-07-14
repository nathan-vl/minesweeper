#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

#define COVERED_CHAR '#'
#define OPEN_CHAR '.'
#define FLAG_CHAR '!'
#define GUESS_CHAR '?'
#define MINE_CHAR 'o'

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

char getTileChar(struct Tile *tile);
char getOpenTileChar(struct Tile *tile);

#endif

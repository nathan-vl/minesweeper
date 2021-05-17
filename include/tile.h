#ifndef TILE
#define TILE

#include <stdbool.h>

#define COVERED '#'
#define OPENED '.'
#define FLAG '!'
#define GUESS '?'
#define MINE 'o'

enum TileStatus
{
    opened,
    flag,
    covered,
    guess
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

#ifndef DISPLAY_C
#define DISPLAY_C

#include "minefield.h"
#include "tile.h"

#define COVERED_TILE_CHAR '#'
#define OPEN_TILE_CHAR '.'
#define FLAG_TILE_CHAR '!'
#define GUESS_TILE_CHAR '?'
#define MINE_TILE_CHAR 'o'

char getTileChar(struct Tile *tile);
char getOpenTileChar(struct Tile *tile);

void displayMinefield(struct Minefield *minefield);
void displayOpenMinefield(struct Minefield *minefield);

#endif

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <stdbool.h>
#include "util.h"

struct Minefield
{
    struct Pos size;
    int mines;

    struct Tile *tiles;
};

struct Minefield newMinefield(const struct Pos pos, const int mines);

void freeMinefield(struct Minefield *minefield);

struct Tile *getTile(struct Minefield *minefield, const struct Pos pos);

bool isInBound(struct Minefield *minefield, const struct Pos pos);

int getNumNeighoursMines(struct Minefield *minefield, struct Pos pos);

void insertMines(struct Minefield *minefield);

void swapTiles(struct Minefield *minefield);

void setNeighboursMinefield(struct Minefield *minefield);

void initMines(struct Minefield *minefield);

void setOpen(struct Tile *tile);

void openNeighboursTiles(struct Minefield *minefield, const struct Pos pos);

struct Tile *openTile(struct Minefield *minefield, const struct Pos pos);

void openFirstTile(struct Minefield *minefield, const struct Pos pos);

void displayMinefield(struct Minefield *minefield);

void displayOpenMinefield(struct Minefield *minefield);

#endif

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <stdbool.h>
#include "util.h"

struct Field
{
    struct Pos size;
    int mines;

    struct Tile **tiles;
};

struct Field newField(const struct Pos pos, const int mines);

void destroyField(struct Field *field);

struct Tile *getTile(struct Field *field, const struct Pos pos);

bool isInBound(struct Field *field, const struct Pos pos);

int getNumNeighoursMines(struct Field *field, struct Pos pos);

void insertMines(struct Field *field);

void swapTiles(struct Field *field);

void setNeighboursField(struct Field *field);

void initMines(struct Field *field);

void setOpen(struct Tile *tile);

void openNeighboursTiles(struct Field *field, const struct Pos pos);

struct Tile *openTile(struct Field *field, const struct Pos pos);

void openFirstTile(struct Field *field, const struct Pos pos);

void displayField(struct Field *field);

void displayOpenField(struct Field *field);

#endif

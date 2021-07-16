#include "minefield.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>

struct Minefield newMinefield(const struct Pos size, const int mines)
{
    struct Minefield minefield;

    minefield.mines = mines;
    minefield.size = size;

    int field_area = size.x * size.y;

    minefield.tiles = malloc(sizeof(struct Tile) * field_area);

    for (int i = 0; i < field_area; i++)
    {
        struct Tile *tile = &minefield.tiles[i];
        tile->status = COVERED;
        tile->hasMine = false;
    }

    return minefield;
}

void freeMinefield(struct Minefield *minefield)
{
    free(minefield->tiles);
}

struct Tile *getTile(struct Minefield *minefield, const struct Pos pos)
{
    return &minefield->tiles[pos.x + pos.y * minefield->size.x];
}

bool isInBound(struct Minefield *minefield, const struct Pos pos)
{
    bool isInBoundX = pos.x >= 0 && pos.x < minefield->size.x;
    bool isInBoundY = pos.y >= 0 && pos.y < minefield->size.y;
    return isInBoundX && isInBoundY;
}

int getNumNeighoursMines(struct Minefield *minefield, struct Pos pos)
{
    int total = 0;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (!(x == 0 && y == 0))
            {
                struct Pos neighbourPos = newPos(pos.x + x, pos.y + y);

                if (isInBound(minefield, neighbourPos))
                {
                    total += getTile(minefield, neighbourPos)->hasMine;
                }
            }
        }
    }

    return total;
}

void insertMines(struct Minefield *minefield)
{
    int insertedMines = 0;

    for (int i = 0; i < minefield->size.x * minefield->size.y; i++)
    {
        struct Tile *tile = &minefield->tiles[i];

        if (insertedMines == minefield->mines)
        {
            return;
        }

        if (tile->status != OPEN)
        {
            tile->hasMine = true;
            insertedMines++;
        }
    }
}

void swapTiles(struct Minefield *minefield)
{
    for (int y = 0; y < minefield->size.y; y++)
    {
        for (int x = 0; x < minefield->size.x; x++)
        {
            struct Tile *currentTile = getTile(minefield, newPos(x, y));
            if (currentTile->status != OPEN)
            {
                struct Pos pos = randomPos(newPos(
                    minefield->size.x - 1,
                    minefield->size.y - 1));

                struct Tile *randomTile = getTile(minefield, pos);

                if (!((pos.x == x && pos.y == y) || getTile(minefield, pos)->status == OPEN))
                {
                    struct Tile temp = *currentTile;
                    *currentTile = *randomTile;
                    *randomTile = temp;
                }
            }
        }
    }
}

void setNeighboursMinefield(struct Minefield *minefield)
{
    for (int y = 0; y < minefield->size.y; y++)
    {
        for (int x = 0; x < minefield->size.x; x++)
        {
            struct Pos pos = {x, y};
            struct Tile *tile = getTile(minefield, pos);
            tile->neighbours = getNumNeighoursMines(minefield, pos);
        }
    }
}

void initMines(struct Minefield *minefield)
{
    insertMines(minefield);
    swapTiles(minefield);
    setNeighboursMinefield(minefield);
}

void openNeighboursTiles(struct Minefield *minefield, const struct Pos pos)
{
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            struct Pos neighbourPos = newPos(pos.x + x, pos.y + y);

            if (isInBound(minefield, neighbourPos) && getTile(minefield, neighbourPos)->status != OPEN)
            {
                openTile(minefield, neighbourPos);
            }
        }
    }
}

struct Tile *openTile(struct Minefield *minefield, const struct Pos pos)
{
    struct Tile *tile = getTile(minefield, pos);

    tile->status = OPEN;

    if (!tile->hasMine && tile->neighbours == 0)
    {
        openNeighboursTiles(minefield, pos);
    }

    return tile;
}

void openFirstTile(struct Minefield *minefield, const struct Pos pos)
{
    getTile(minefield, pos)->status = OPEN;

    initMines(minefield);
    openTile(minefield, pos);
}

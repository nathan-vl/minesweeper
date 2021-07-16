#include <stdio.h>

#include "display.h"
#include "minefield.h"
#include "tile.h"
#include "util.h"

char getTileChar(struct Tile *tile)
{
    switch (tile->status)
    {
    case COVERED:
        return COVERED_TILE_CHAR;
    case FLAG:
        return FLAG_TILE_CHAR;
    case GUESS:
        return GUESS_TILE_CHAR;
    default:
        if (tile->hasMine)
        {
            return MINE_TILE_CHAR;
        }
        else if (tile->neighbours != 0)
        {
            return tile->neighbours + '0';
        }
    }
    return OPEN_TILE_CHAR;
}

char getOpenTileChar(struct Tile *tile)
{
    if (tile->hasMine)
    {
        return MINE_TILE_CHAR;
    }
    else if (tile->neighbours != 0)
    {
        return tile->neighbours + '0';
    }

    return OPEN_TILE_CHAR;
}

void displayMinefield(struct Minefield *minefield)
{
    for (int y = 0; y < minefield->size.y; y++)
    {
        for (int x = 0; x < minefield->size.x; x++)
        {
            struct Pos pos = newPos(x, y);
            printf("%c", getTileChar(getTile(minefield, pos)));
        }
        printf("\n");
    }
}

void displayOpenMinefield(struct Minefield *minefield)
{
    for (int y = 0; y < minefield->size.y; y++)
    {
        for (int x = 0; x < minefield->size.x; x++)
        {
            struct Pos pos = newPos(x, y);
            printf("%c", getOpenTileChar(getTile(minefield, pos)));
        }
        printf("\n");
    }
}

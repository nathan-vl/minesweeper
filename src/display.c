#include <stdio.h>
#include "display.h"
#include "minesweeper_game.h"
#include "tile.h"
#include "util.h"

#define COVERED_TILE_CHAR '#'
#define OPEN_TILE_CHAR '.'
#define FLAG_TILE_CHAR '!'
#define GUESS_TILE_CHAR '?'
#define MINE_TILE_CHAR 'o'

char getTileChar(const struct Tile *tile)
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

char getOpenTileChar(const struct Tile *tile)
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

void displayMinesweeperGame(const struct MinesweeperGame *game)
{
    for (int y = 0; y < game->size.y; y++)
    {
        for (int x = 0; x < game->size.x; x++)
        {
            struct Pos pos = newPos(x, y);
            printf("%c", getTileChar(getTile(game, pos)));
        }
        printf("\n");
    }
}

void displayOpenMinesweeperGame(const struct MinesweeperGame *game)
{
    for (int y = 0; y < game->size.y; y++)
    {
        for (int x = 0; x < game->size.x; x++)
        {
            struct Pos pos = newPos(x, y);
            printf("%c", getOpenTileChar(getTile(game, pos)));
        }
        printf("\n");
    }
}

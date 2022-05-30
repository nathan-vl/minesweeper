#include <stdio.h>
#include <string.h>
#include "minesweeper_game.h"
#include "terminal_frontend.h"
#include "tile.h"
#include "util.h"

#define COVERED_TILE_CHAR '#'
#define OPEN_TILE_CHAR '.'
#define FLAG_TILE_CHAR '!'
#define GUESS_TILE_CHAR '?'
#define MINE_TILE_CHAR 'o'

char getTileChar(TileStatus status, _Bool has_mine, int neighbours)
{
    switch (status)
    {
    case COVERED:
        return COVERED_TILE_CHAR;
    case FLAG:
        return FLAG_TILE_CHAR;
    case GUESS:
        return GUESS_TILE_CHAR;
    default:
        if (has_mine)
            return MINE_TILE_CHAR;

        if (neighbours != 0)
            return neighbours + '0';
    }

    return OPEN_TILE_CHAR;
}

char getOpenTileChar(_Bool has_mine, int neighbours)
{
    if (has_mine)
        return MINE_TILE_CHAR;
    if (neighbours != 0)
        return neighbours + '0';

    return OPEN_TILE_CHAR;
}

void displayMinesweeperGame(Pos size, Tiles tiles)
{
    for (size_t y = 0; y < size.y; ++y)
    {
        for (size_t x = 0; x < size.x; ++x)
        {
            int i = y * size.x + x;
            printf("%c", getTileChar(tiles.status[i], tiles.mines[i], tiles.neighbours[i]));
        }
        printf("\n");
    }
}

void displayOpenMinesweeperGame(Pos size, Tiles tiles)
{
    for (size_t y = 0; y < size.y; ++y)
    {
        for (size_t x = 0; x < size.x; ++x)
        {
            int i = y * size.x + x;
            printf("%c", getOpenTileChar(tiles.mines[i], tiles.neighbours[i]));
        }
        printf("\n");
    }
}

Action getAction(MinesweeperGame *game)
{
    _Bool input_is_valid;
    Action action;

    char line[15];

    do
    {
        input_is_valid = 1;

        printf("> ");

        int res = scanf("%[^\n]%*c", line);

        if (res == 0)
            continue;

        if (sscanf(line, "f %zu %zu", &action.pos.x, &action.pos.y) == 2)
            action.type = FLAG_TILE_ACTION;
        else if (sscanf(line, "g %zu %zu", &action.pos.x, &action.pos.y) == 2)
            action.type = GUESS_TILE_ACTION;
        else if (sscanf(line, "%zu %zu", &action.pos.x, &action.pos.y) == 2)
            action.type = OPEN_TILE_ACTION;
        else
            input_is_valid = 0;

        if (!isInBoundPos(game->size, action.pos))
            input_is_valid = 0;
    } while (!input_is_valid);

    return action;
}

void playGame(MinesweeperGame *game)
{
    const char *WON_TEXT = "Congratulations, you won!\n";
    const char *LOST_TEXT = "Sorry, you lost.\n";

    while (game->status == PROGRESS)
    {
        displayMinesweeperGame(game->size, game->tiles);

        doAction(game, getAction(game));
    }

    displayOpenMinesweeperGame(game->size, game->tiles);
    printf("%s", (game->status == WON) ? WON_TEXT : LOST_TEXT);
}

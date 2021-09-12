#include "minesweeper_game.h"
#include "terminal_frontend.h"
#include "tile.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

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
            return MINE_TILE_CHAR;
        else if (tile->neighbours != 0)
            return tile->neighbours + '0';
    }

    return OPEN_TILE_CHAR;
}

char getOpenTileChar(const struct Tile *tile)
{
    if (tile->hasMine)
        return MINE_TILE_CHAR;
    else if (tile->neighbours != 0)
        return tile->neighbours + '0';

    return OPEN_TILE_CHAR;
}

void displayMinesweeperGame(const struct MinesweeperGame *game)
{
    for (int y = 0; y < game->size.y; y++)
    {
        for (int x = 0; x < game->size.x; x++)
        {
            printf("%c", getTileChar(getTile(game, newPos(x, y))));
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
            printf("%c", getOpenTileChar(getTile(game, newPos(x, y))));
        }
        printf("\n");
    }
}

struct Action getAction(struct MinesweeperGame *game)
{
    _Bool inputIsValid;
    struct Action action;

    char line[15];

    do
    {
        inputIsValid = 1;

        printf("> ");

        scanf("%[^\n]%*c", line);

        if (sscanf(line, "f %i %i", &action.pos.x, &action.pos.y) == 2)
            action.type = FLAG_TILE_ACTION;
        else if (sscanf(line, "g %i %i", &action.pos.x, &action.pos.y) == 2)
            action.type = GUESS_TILE_ACTION;
        else if (sscanf(line, "%i %i", &action.pos.x, &action.pos.y) == 2)
            action.type = OPEN_TILE_ACTION;
        else
            inputIsValid = 0;

        if (!isInBound(game->size, action.pos))
            inputIsValid = 0;
    } while (!inputIsValid);

    return action;
}

void playGame(struct MinesweeperGame *game)
{
    const char *WON_TEXT = "Congratulations, you won!\n";
    const char *LOST_TEXT = "Sorry, you lost.\n";

    while (game->status == PROGRESS)
    {
        displayMinesweeperGame(game);

        doAction(game, getAction(game));
    }

    displayOpenMinesweeperGame(game);
    printf("%s", (game->status == WON) ? WON_TEXT : LOST_TEXT);
}

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

char get_tile_char(const struct Tile *tile)
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
        if (tile->has_mine)
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

char get_open_tile_char(const struct Tile *tile)
{
    if (tile->has_mine)
        return MINE_TILE_CHAR;
    else if (tile->neighbours != 0)
        return tile->neighbours + '0';

    return OPEN_TILE_CHAR;
}

void display_minesweeper_game(const struct MinesweeperGame *game)
{
    for (int y = 0; y < game->size.y; y++)
    {
        for (int x = 0; x < game->size.x; x++)
        {
            printf("%c", get_tile_char(get_tile(game, new_pos(x, y))));
        }
        printf("\n");
    }
}

void display_open_minesweeper_game(const struct MinesweeperGame *game)
{
    for (int y = 0; y < game->size.y; y++)
    {
        for (int x = 0; x < game->size.x; x++)
        {
            printf("%c", get_open_tile_char(get_tile(game, new_pos(x, y))));
        }
        printf("\n");
    }
}

struct Action get_action(struct MinesweeperGame *game)
{
    _Bool input_is_valid;
    struct Action action;

    char line[15];

    do
    {
        input_is_valid = 1;

        printf("> ");

        scanf("%[^\n]%*c", line);

        if (sscanf(line, "f %i %i", &action.pos.x, &action.pos.y) == 2)
        {
            action.type = FLAG_TILE_ACTION;
        }
        else if (sscanf(line, "g %i %i", &action.pos.x, &action.pos.y) == 2)
        {
            action.type = GUESS_TILE_ACTION;
        }
        else if (sscanf(line, "%i %i", &action.pos.x, &action.pos.y) == 2)
        {
            action.type = OPEN_TILE_ACTION;
        }
        else
        {
            input_is_valid = 0;
        }

        if (!is_in_bound(game->size, action.pos))
        {
            input_is_valid = 0;
        }
    } while (!input_is_valid);

    return action;
}

void play_game(struct MinesweeperGame *game)
{
    const char *WON_TEXT = "Congratulations, you won!\n";
    const char *LOST_TEXT = "Sorry, you lost.\n";

    while (game->status == PROGRESS)
    {
        display_minesweeper_game(game);

        do_action(game, get_action(game));
    }

    display_open_minesweeper_game(game);
    printf("%s", (game->status == WON) ? WON_TEXT : LOST_TEXT);
}

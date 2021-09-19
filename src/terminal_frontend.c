#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper_game.h"
#include "terminal_frontend.h"
#include "tile.h"
#include "util.h"

#define ANSI_ESC "\x1b"

#define BOLD "1"

#define FG "3"

#define RED "1"
#define GREEN "2"
#define YELLOW "3"
#define BLUE "4"
#define MAGENTA "5"
#define CYAN "6"

#define WITH ";"

#define FMT(style) ANSI_ESC "[" style "m"
#define FMT_SIMPLE(style, str) FMT(style) str FMT("")

#define COVERED_TILE_CHAR "#"
#define FLAG_TILE_CHAR "!"
#define GUESS_TILE_CHAR "?"
#define MINE_TILE_CHAR "o"

const char *neighbours_display_tile[] = {
    ".",
    FMT_SIMPLE(FG BLUE, "1"),
    FMT_SIMPLE(FG GREEN, "2"),
    FMT_SIMPLE(FG YELLOW, "3"),
    FMT_SIMPLE(FG RED, "4"),
    FMT_SIMPLE(FG BLUE WITH BOLD, "5"),
    FMT_SIMPLE(FG GREEN WITH BOLD, "6"),
    FMT_SIMPLE(FG YELLOW WITH BOLD, "7"),
    FMT_SIMPLE(FG RED WITH BOLD, "8"),
};

const char *get_display_tile(const struct Tile *tile)
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
    }

    return neighbours_display_tile[tile->neighbours];
}

const char *get_display_open_tile(const struct Tile *tile)
{
    if (tile->has_mine)
    {
        return MINE_TILE_CHAR;
    }
    return neighbours_display_tile[tile->neighbours];
}

void display_minesweeper_game(const struct MinesweeperGame *game)
{
    for (size_t y = 0; y < game->size.y; y++)
    {
        for (size_t x = 0; x < game->size.x; x++)
        {
            struct Pos pos = {
                .x = x,
                .y = y
            };
            printf("%s", get_display_tile(get_tile(game, pos)));
        }
        printf("\n");
    }
}

void display_open_minesweeper_game(const struct MinesweeperGame *game)
{
    for (size_t y = 0; y < game->size.y; y++)
    {
        for (size_t x = 0; x < game->size.x; x++)
        {
            struct Pos pos = {
                .x = x,
                .y = y
            };
            printf("%s", get_display_open_tile(get_tile(game, pos)));
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

        if (sscanf(line, "f %zu %zu", &action.pos.x, &action.pos.y) == 2)
        {
            action.type = FLAG_TILE_ACTION;
        }
        else if (sscanf(line, "g %zu %zu", &action.pos.x, &action.pos.y) == 2)
        {
            action.type = GUESS_TILE_ACTION;
        }
        else if (sscanf(line, "%zu %zu", &action.pos.x, &action.pos.y) == 2)
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

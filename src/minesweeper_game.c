#include <stdlib.h>
#include "minesweeper_game.h"
#include "tile.h"
#include "util.h"

struct MinesweeperGame new_minesweeper_game(struct Pos size, int mines)
{
    size_t field_area = size.x * size.y;
    struct MinesweeperGame game = {
        .status = PROGRESS,
        .has_opened_first_tile = 0,
        .size = size,
        .mines = mines,
        .tiles = malloc(sizeof(struct Tile) * field_area)
    };

    for (size_t i = 0; i < field_area; ++i)
    {
        struct Tile *tile = &game.tiles[i];
        tile->status = COVERED;
        tile->has_mine = 0;
    }

    return game;
}

void free_minesweeper_game(struct MinesweeperGame *game)
{
    free(game->tiles);
}

struct Tile *get_tile(const struct MinesweeperGame *game, struct Pos pos)
{
    return &game->tiles[pos.x + pos.y * game->size.x];
}

void open_tile(struct MinesweeperGame *game, struct Pos pos);
void open_neighbouring_tiles(struct MinesweeperGame *game, struct Pos pos)
{
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            struct Pos neighbour_pos = {
                .x = pos.x + x,
                .y = pos.y + y
            };

            if (is_in_bound(game->size, neighbour_pos) && get_tile(game, neighbour_pos)->status != OPEN)
            {
                open_tile(game, neighbour_pos);
            }
        }
    }
}

void open_tile(struct MinesweeperGame *game, struct Pos pos)
{
    struct Tile *tile = get_tile(game, pos);

    tile->status = OPEN;

    if (!tile->has_mine && tile->neighbours == 0)
    {
        open_neighbouring_tiles(game, pos);
    }
}

void insert_mines(struct MinesweeperGame *game)
{
    int inserted_mines = 0;

    size_t index = 0;
    while (inserted_mines < game->mines)
    {
        struct Tile *tile = &game->tiles[index];

        if (tile->status != OPEN)
        {
            tile->has_mine = 1;
            ++inserted_mines;
        }
        ++index;
    }
}

void swap_tiles(struct MinesweeperGame *game)
{
    for (size_t i = 0; i < game->size.x * game->size.y; ++i)
    {
        struct Tile *current_tile = &game->tiles[i];

        if (current_tile->status == OPEN)
        {
            continue;
        }

        size_t random_index = random_int(0, game->size.x * game->size.y - 1);

        struct Tile *random_tile = &game->tiles[random_index];

        if (i != random_index && random_tile->status != OPEN)
        {
            struct Tile temp = *current_tile;
            *current_tile = *random_tile;
            *random_tile = temp;
        }
    }
}

int num_neighours_mines(struct MinesweeperGame *game, struct Pos pos)
{
    int total = 0;

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            struct Pos neighbour_pos = {
                .x = pos.x + x,
                .y = pos.y + y
            };

            if (is_in_bound(game->size, neighbour_pos))
            {
                total += get_tile(game, neighbour_pos)->has_mine;
            }
        }
    }

    return total;
}

void update_neighbours(struct MinesweeperGame *game)
{
    for (size_t y = 0; y < game->size.y; ++y)
    {
        for (size_t x = 0; x < game->size.x; ++x)
        {
            struct Pos pos = {
                .x = x,
                .y = y
            };
            get_tile(game, pos)->neighbours = num_neighours_mines(game, pos);
        }
    }
}

_Bool check_victory(struct MinesweeperGame *game)
{
    for (size_t i = 0; i < game->size.x * game->size.y; ++i)
    {
        struct Tile tile = game->tiles[i];
        if (tile.status == COVERED && !tile.has_mine)
        {
            return 0;
        }
    }

    return 1;
}

void open_first_tile(struct MinesweeperGame *game, struct Pos pos)
{
    game->started_time = time(NULL);
    srand(game->started_time);

    get_tile(game, pos)->status = OPEN;

    insert_mines(game);
    swap_tiles(game);
    update_neighbours(game);

    open_tile(game, pos);
}

void do_action(struct MinesweeperGame *game, struct Action action)
{
    struct Tile *tile = get_tile(game, action.pos);

    if (action.type == OPEN_TILE_ACTION)
    {
        if (game->has_opened_first_tile)
        {
            open_tile(game, action.pos);
            if (tile->has_mine)
            {
                game->status = LOST;
            }
        }
        else
        {
            open_first_tile(game, action.pos);
            game->has_opened_first_tile = 1;
        }

        if (check_victory(game))
        {
            game->status = WON;
        }
    }
    else if (tile->status != OPEN)
    {
        if (action.type == FLAG_TILE_ACTION)
        {
            tile->status = FLAG;
        }
        else if (action.type == GUESS_TILE_ACTION)
        {
            tile->status = GUESS;
        }
    }
}

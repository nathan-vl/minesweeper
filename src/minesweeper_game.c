#include <stdlib.h>
#include "minesweeper_game.h"
#include "tile.h"
#include "util.h"

MinesweeperGame newMinesweeperGame(Pos size, int mines)
{
    size_t field_area = size.x * size.y;
    MinesweeperGame game = {
        .status = PROGRESS,
        .has_opened_first_tile = 0,
        .size = size,
        .mines = mines,
        .tiles.mines = malloc(sizeof(_Bool) * field_area),
        .tiles.neighbours = malloc(sizeof(short) * field_area),
        .tiles.status = malloc(sizeof(TileStatus) * field_area),
    };

    for (size_t i = 0; i < field_area; ++i)
    {
        game.tiles.mines[i] = 0;
        game.tiles.status[i] = COVERED;
    }

    return game;
}

void freeMinesweeperGame(MinesweeperGame *game)
{
    free(game->tiles.mines);
    free(game->tiles.neighbours);
    free(game->tiles.status);
}

void openNeighbouringTiles(Pos size, Tiles *tiles, int pos)
{
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            size_t neighbour_pos = x + pos * (1 + y);

            if (neighbour_pos < (size.x * size.y) && tiles->status[neighbour_pos] != OPEN)
            {
                tiles->status[pos] = OPEN;
                if (!tiles->mines[pos] && tiles->neighbours[pos] == 0)
                    openNeighbouringTiles(size, tiles, neighbour_pos);
            }
        }
    }
}

void insertMines(Tiles *tiles, int mines)
{
    int inserted_mines = 0;

    size_t index = 0;
    while (inserted_mines < mines)
    {
        if (tiles->status[index] == OPEN)
            continue;

        tiles->mines[index] = 1;
        ++inserted_mines;
        ++index;
    }
}

void swapTiles(MinesweeperGame *game)
{
    for (size_t i = 0; i < game->size.x * game->size.y; ++i)
    {
        if (game->tiles.status[i] == OPEN)
            continue;

        size_t random_index = randomInt(0, game->size.x * game->size.y - 1);

        if (i != random_index && game->tiles.status[random_index] != OPEN)
        {
            _Bool tmp = game->tiles.mines[i];
            game->tiles.mines[i] = game->tiles.mines[random_index];
            game->tiles.mines[random_index] = tmp;
        }
    }
}

int numNeighoursMines(Pos size, _Bool *mines, int pos)
{
    int total = 0;

    for (int y = -1; y <= 1; ++y)
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0)
                continue;

            size_t neighbour_pos = x + pos * (1 + y);

            if (neighbour_pos < (size.x * size.y) && mines[neighbour_pos])
                ++total;
        }

    return total;
}

void updateNeighbours(Pos size, Tiles tiles)
{
    for (size_t i = 0; i < size.x * size.y; i++)
        tiles.neighbours[i] = numNeighoursMines(size, tiles.mines, i);
}

_Bool checkVictory(Pos size, Tiles tiles)
{
    for (size_t i = 0; i < size.x * size.y; ++i)
        if (tiles.status[i] == COVERED && !tiles.mines[i])
            return 0;

    return 1;
}

void openFirstTile(MinesweeperGame *game, int pos)
{
    game->started_time = time(NULL);
    srand(game->started_time);

    game->tiles.status[pos] = OPEN;

    insertMines(&game->tiles, game->mines);
    swapTiles(game);
    updateNeighbours(game->size, game->tiles);

    openNeighbouringTiles(game->size, &game->tiles, pos);
}

void doAction(MinesweeperGame *game, Action action)
{
    int pos = action.pos.y * game->size.x + action.pos.x;
    if (action.type == OPEN_TILE_ACTION)
    {
        if (game->has_opened_first_tile)
        {
            openNeighbouringTiles(game->size, &game->tiles, pos);
            if (game->tiles.mines[pos])
                game->status = LOST;
        }
        else
        {
            openFirstTile(game, pos);
            game->has_opened_first_tile = 1;
        }

        if (checkVictory(game->size, game->tiles))
            game->status = WON;
    }
    else if (game->tiles.status[pos] != OPEN)
    {
        if (action.type == FLAG_TILE_ACTION)
            game->tiles.status[pos] = FLAG;
        else if (action.type == GUESS_TILE_ACTION)
            game->tiles.status[pos] = GUESS;
    }
}

#include <cstdlib>
#include "minesweeper_game.hpp"
#include "tile.hpp"
#include "util.hpp"

MinesweeperGame::MinesweeperGame(Pos size, int mines)
{
    this->size = size;
    this->mines = mines;

    auto field_area = size.x * size.y;
    status = GameStatus::PROGRESS;
    has_opened_first_tile = false;

    tiles.mines = new bool[field_area];
    tiles.neighbours = new short[field_area];
    tiles.status = new TileStatus[field_area];

    for (auto i = 0; i < field_area; ++i)
    {
        tiles.mines[i] = 0;
        tiles.status[i] = TileStatus::COVERED;
    }
}

MinesweeperGame::~MinesweeperGame()
{
    delete tiles.mines;
    delete tiles.neighbours;
    delete tiles.status;
}

void openNeighbouringTiles(Pos size, Tiles *tiles, int pos)
{
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            auto neighbour_pos = x + pos * (1 + y);

            if (neighbour_pos < (size.x * size.y) && tiles->status[neighbour_pos] != TileStatus::OPEN)
            {
                tiles->status[pos] = TileStatus::OPEN;
                if (!tiles->mines[pos] && tiles->neighbours[pos] == 0)
                    openNeighbouringTiles(size, tiles, neighbour_pos);
            }
        }
    }
}

void insertMines(Tiles *tiles, int mines)
{
    int inserted_mines = 0;

    auto index = 0;
    while (inserted_mines < mines)
    {
        if (tiles->status[index] == TileStatus::OPEN)
            continue;

        tiles->mines[index] = 1;
        ++inserted_mines;
        ++index;
    }
}

void swapTiles(MinesweeperGame *game)
{
    for (auto i = 0; i < game->size.x * game->size.y; ++i)
    {
        if (game->tiles.status[i] == TileStatus::OPEN)
            continue;

        auto random_index = randomInt(0, game->size.x * game->size.y - 1);

        if (i != random_index && game->tiles.status[random_index] != TileStatus::OPEN)
        {
            bool tmp = game->tiles.mines[i];
            game->tiles.mines[i] = game->tiles.mines[random_index];
            game->tiles.mines[random_index] = tmp;
        }
    }
}

int numNeighoursMines(Pos size, bool *mines, int pos)
{
    int total = 0;

    for (int y = -1; y <= 1; ++y)
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0)
                continue;

            auto neighbour_pos = x + pos * (1 + y);

            if (neighbour_pos < (size.x * size.y) && mines[neighbour_pos])
                ++total;
        }

    return total;
}

void updateNeighbours(Pos size, Tiles tiles)
{
    for (auto i = 0; i < size.x * size.y; i++)
        tiles.neighbours[i] = numNeighoursMines(size, tiles.mines, i);
}

bool checkVictory(Pos size, Tiles tiles)
{
    for (auto i = 0; i < size.x * size.y; ++i)
        if (tiles.status[i] == TileStatus::COVERED && !tiles.mines[i])
            return 0;

    return 1;
}

void openFirstTile(MinesweeperGame *game, int pos)
{
    game->started_time = time(nullptr);
    srand(game->started_time);

    game->tiles.status[pos] = TileStatus::OPEN;

    insertMines(&game->tiles, game->mines);
    swapTiles(game);
    updateNeighbours(game->size, game->tiles);

    openNeighbouringTiles(game->size, &game->tiles, pos);
}


void MinesweeperGame::doAction(Action action)
{
    int pos = action.pos.y * size.x + action.pos.x;
    if (action.type == PlayerAction::OPEN_TILE)
    {
        if (has_opened_first_tile)
        {
            openNeighbouringTiles(size, &tiles, pos);
            if (tiles.mines[pos])
                status = GameStatus::LOST;
        }
        else
        {
            openFirstTile(this, pos);
            has_opened_first_tile = 1;
        }

        if (checkVictory(size, tiles))
            status = GameStatus::WON;
    }
    else if (tiles.status[pos] != TileStatus::OPEN)
    {
        if (action.type == PlayerAction::FLAG_TILE)
            tiles.status[pos] = TileStatus::FLAG;
        else if (action.type == PlayerAction::GUESS_TILE)
            tiles.status[pos] = TileStatus::GUESS;
    }
}

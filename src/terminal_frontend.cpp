#include <iostream>
#include "minesweeper_game.hpp"
#include "terminal_frontend.hpp"
#include "tile.hpp"
#include "util.hpp"

#define COVERED_TILE_CHAR '#'
#define OPEN_TILE_CHAR '.'
#define FLAG_TILE_CHAR '!'
#define GUESS_TILE_CHAR '?'
#define MINE_TILE_CHAR 'o'

char getTileChar(TileStatus status, bool has_mine, int neighbours)
{
    switch (status)
    {
    case TileStatus::COVERED:
        return COVERED_TILE_CHAR;
    case TileStatus::FLAG:
        return FLAG_TILE_CHAR;
    case TileStatus::GUESS:
        return GUESS_TILE_CHAR;
    default:
        if (has_mine)
            return MINE_TILE_CHAR;

        if (neighbours != 0)
            return neighbours + '0';
    }

    return OPEN_TILE_CHAR;
}

char getOpenTileChar(bool has_mine, int neighbours)
{
    if (has_mine)
        return MINE_TILE_CHAR;
    if (neighbours != 0)
        return neighbours + '0';

    return OPEN_TILE_CHAR;
}

void displayMinesweeperGame(Pos size, Tiles tiles)
{
    for (auto y = 0; y < size.y; ++y)
    {
        for (auto x = 0; x < size.x; ++x)
        {
            int i = y * size.x + x;
            std::cout << getTileChar(tiles.status[i], tiles.mines[i], tiles.neighbours[i]);
        }
        std::cout << "\n";
    }
}

void displayOpenMinesweeperGame(Pos size, Tiles tiles)
{
    for (auto y = 0; y < size.y; ++y)
    {
        for (auto x = 0; x < size.x; ++x)
        {
            int i = y * size.x + x;
            std::cout << getOpenTileChar(tiles.mines[i], tiles.neighbours[i]);
        }
        std::cout << "\n";
    }
}

Action getAction(MinesweeperGame *game)
{
    bool input_is_valid;
    Action action;

    char line[15];

    do
    {
        input_is_valid = 1;

        std::cout << "> ";

        int res = scanf("%[^\n]%*c", line);

        if (res == 0)
            continue;

        if (sscanf(line, "f %zu %zu", &action.pos.x, &action.pos.y) == 2)
            action.type = PlayerAction::FLAG_TILE;
        else if (sscanf(line, "g %zu %zu", &action.pos.x, &action.pos.y) == 2)
            action.type = PlayerAction::GUESS_TILE;
        else if (sscanf(line, "%zu %zu", &action.pos.x, &action.pos.y) == 2)
            action.type = PlayerAction::OPEN_TILE;
        else
            input_is_valid = 0;

        if (!isInBoundPos(game->size, action.pos))
            input_is_valid = 0;
    } while (!input_is_valid);

    return action;
}

void playGame(MinesweeperGame *game)
{
    while (game->status == GameStatus::PROGRESS)
    {
        displayMinesweeperGame(game->size, game->tiles);

        game->doAction(getAction(game));
    }

    displayOpenMinesweeperGame(game->size, game->tiles);
    if (game->status == GameStatus::WON) {
        std::cout << "Game over, you won!\n";
    } else {
        std::cout << "Game over, you lost.\n";
    }
}

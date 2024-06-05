#pragma once

#include <ctime>
#include "util.hpp"
#include "tile.hpp"

enum class PlayerAction
{
    OPEN_TILE,
    FLAG_TILE,
    GUESS_TILE,
};

struct Action
{
    PlayerAction type;
    Pos pos;
};

enum class GameStatus
{
    PROGRESS,
    WON,
    LOST
};

struct MinesweeperGame
{
    Tiles tiles;
    Pos size;
    int mines;
    bool has_opened_first_tile;
    GameStatus status;
    time_t started_time;

    MinesweeperGame(Pos size, int mines);
    ~MinesweeperGame();

    void doAction(Action action);
};

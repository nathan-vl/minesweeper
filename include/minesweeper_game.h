#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <time.h>
#include "util.h"
#include "tile.h"

typedef enum PlayerAction
{
    OPEN_TILE_ACTION,
    FLAG_TILE_ACTION,
    GUESS_TILE_ACTION,
} PlayerAction;

typedef struct Action
{
    PlayerAction type;
    Pos pos;
} Action;

typedef enum GameStatus
{
    PROGRESS,
    WON,
    LOST
} GameStatus;

typedef struct MinesweeperGame
{
    time_t started_time;
    GameStatus status;
    _Bool has_opened_first_tile;

    Pos size;
    int mines;

    Tiles tiles;
} MinesweeperGame;

MinesweeperGame newMinesweeperGame(Pos size, int mines);
void freeMinesweeperGame(MinesweeperGame *game);

void doAction(MinesweeperGame *game, Action action);

#endif

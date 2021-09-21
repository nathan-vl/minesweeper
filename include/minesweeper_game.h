#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <time.h>
#include "util.h"

enum PlayerAction
{
    OPEN_TILE_ACTION,
    FLAG_TILE_ACTION,
    GUESS_TILE_ACTION,
};

struct Action
{
    enum PlayerAction type;
    struct Pos pos;
};

enum GameStatus
{
    PROGRESS,
    WON,
    LOST
};

struct MinesweeperGame
{
    time_t started_time;
    enum GameStatus status;
    _Bool has_opened_first_tile;

    struct Pos size;
    int mines;

    struct Tile *tiles;
};

struct MinesweeperGame new_minesweeper_game(struct Pos size, int mines);
void free_minesweeper_game(struct MinesweeperGame *game);

struct Tile *get_tile(const struct MinesweeperGame *game, struct Pos pos);

void do_action(struct MinesweeperGame *game, struct Action action);

#endif

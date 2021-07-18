#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <stdbool.h>
#include "util.h"

enum PlayerAction
{
    OPEN_TILE_ACTION,
    FLAG_TILE_ACTION,
    GUESS_TILE_ACTION,
    DISPLAY_HELP_ACTION
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
    enum GameStatus status;
    bool hasOpenedFirstTile;

    struct Pos size;
    int mines;

    struct Tile *tiles;
};

struct MinesweeperGame newMinesweeperGame(const struct Pos size, const int mines);
void freeMinesweeperGame(struct MinesweeperGame *game);

void playGame(struct MinesweeperGame *game);
struct Tile *getTile(struct MinesweeperGame *game, const struct Pos pos);

#endif

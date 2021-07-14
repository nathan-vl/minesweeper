#ifndef GAME_H
#define GAME_H

#include "minefield.h"

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

struct Game
{
    struct Field field;
    enum GameStatus status;
    bool hasOpenedFirstTile;
};

struct Game newGame(const struct Pos size, const int mines);
void freeGame(struct Game *game);

void playGame(struct Game *game);

#endif

#include "minefield.h"

enum TypeAction
{
    openTileAction,
    flagTileAction,
    guessTileAction,
    helpAction
};

struct Action
{
    enum TypeAction type;
    struct Pos pos;
};

enum GameStatus
{
    progress,
    won,
    lost
};

struct Game
{
    struct Field field;
    enum GameStatus status;
    bool hasOpenedFirstTile;
};

struct Game newGame(const struct Pos size, const int mines);
void destroyGame(struct Game *game);

void playGame(struct Game *game);
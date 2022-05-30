#include <stdio.h>
#include <string.h>
#include "minesweeper_game.h"
#include "terminal_frontend.h"

int parseArgs(int argc, const char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        const char *arg = argv[i];

        if (strcmp(arg, "--help") == 0)
        {
            printf("Minesweeper 0.1.0\n");
            return 0;
        }

        printf("Usage: minesweeper [--help]\n");
        return 1;
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
        return parseArgs(argc, argv);

    MinesweeperGame game = newMinesweeperGame((Pos){8, 8}, 16);

    playGame(&game);

    freeMinesweeperGame(&game);

    return 0;
}

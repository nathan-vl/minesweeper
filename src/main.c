#include "minesweeper_game.h"
#include <terminal_frontend.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            const char *arg = argv[i];

            if (strcmp(arg, "--help") == 0)
            {
                printf("Minesweeper 0.1.0\n");
                return 0;
            }
            else
            {
                printf("Usage: minesweeper [--help]\n");
                return 1;
            }
        }
    }

    srand(time(NULL));

    struct MinesweeperGame game = newMinesweeperGame((struct Pos){8, 8}, 16);

    playGame(&game);

    freeMinesweeperGame(&game);

    return 0;
}

#include <stdio.h>
#include <string.h>
#include "minesweeper_game.h"
#include "terminal_frontend.h"

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
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

    struct MinesweeperGame game = new_minesweeper_game((struct Pos){8, 8}, 16);

    play_game(&game);

    free_minesweeper_game(&game);

    return 0;
}

#include "util.h"
#include "minesweeper_game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));

    struct MinesweeperGame game = newMinesweeperGame((struct Pos){8, 8}, 16);

    playGame(&game);

    freeMinesweeperGame(&game);

    return 0;
}

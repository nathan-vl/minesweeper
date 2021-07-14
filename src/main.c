#include "util.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    struct Game game = newGame((struct Pos){8, 8}, 16);

    playGame(&game);

    destroyGame(&game);

    return 0;
}

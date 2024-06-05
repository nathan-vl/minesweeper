#include <iostream>
#include <string>
#include "minesweeper_game.hpp"
#include "terminal_frontend.hpp"

int parseArgs(int argc, const char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        const char *arg = argv[i];

        if (std::string("--help").compare(arg) == 0)
        {
            std::cout << "Minesweeper 0.2.0\n";
            return EXIT_SUCCESS;
        } else {
            std::cout << "Usage: minesweeper [--help]\n";
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

int main(int argc, const char *argv[])
{
    if (argc > 1)
    {
        return parseArgs(argc, argv);
    }

    auto game = MinesweeperGame((Pos){8, 8}, 16);

    playGame(&game);

    return EXIT_SUCCESS;
}

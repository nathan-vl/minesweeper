#include "game.h"
#include "minefield.h"
#include "tile.h"
#include <stdio.h>
#include <string.h>

struct Game newGame(const struct Pos size, const int mines)
{
    return (struct Game){newField(size, mines), PROGRESS, false};
}

void freeGame(struct Game *game)
{
    freeField(&game->field);
}

struct Action getAction(struct Field *field)
{
    bool inputIsValid = false;
    struct Action action = {DISPLAY_HELP_ACTION, {-1, -1}};
    char line[15];

    do
    {
        printf("> ");

        scanf("%[^\n]%*c", line);

        if (sscanf(line, "f %i %i", &action.pos.x, &action.pos.y) == 2 && isInBound(field, action.pos))
        {
            action.type = FLAG_TILE_ACTION;
            inputIsValid = true;
        }
        else if (sscanf(line, "g %i %i", &action.pos.x, &action.pos.y) == 2 && isInBound(field, action.pos))
        {
            action.type = GUESS_TILE_ACTION;
            inputIsValid = true;
        }
        else if (sscanf(line, "%i %i", &action.pos.x, &action.pos.y) == 2 && isInBound(field, action.pos))
        {
            action.type = OPEN_TILE_ACTION;
            inputIsValid = true;
        }
        else if (strcmp(line, "help") == 0 || strcmp(line, "?") == 0)
        {
            inputIsValid = true;
        }
    } while (!inputIsValid);

    return action;
}

void doAction(struct Action action, struct Game *game)
{
    if (action.type == DISPLAY_HELP_ACTION)
    {
        printf("Available commands:\n");

        printf("Type \"help\" or \"?\" to show this message.\n");
        printf("f 2 3 to put a flag at (2, 3)\n");
        printf("g 2 3 to put a guess at (2, 3)\n");
        printf("2 3 to open tile at (2, 3)\n");
    }
    else
    {
        struct Tile *tile = getTile(&game->field, action.pos);
        if (action.type == OPEN_TILE_ACTION)
        {
            if (game->hasOpenedFirstTile)
            {
                openTile(&game->field, action.pos);
                if (tile->hasMine)
                {
                    game->status = LOST;
                }
            }
            else
            {
                openFirstTile(&game->field, action.pos);
                game->hasOpenedFirstTile = true;
            }
        }
        if (tile->status != OPEN)
        {
            if (action.type == FLAG_TILE_ACTION)
            {
                tile->status = FLAG;
            }
            else if (action.type == GUESS_TILE_ACTION)
            {
                tile->status = GUESS;
            }
        }
    }
}

void playGame(struct Game *game)
{
    while (game->status == PROGRESS)
    {
        displayField(&game->field);

        struct Action action = getAction(&game->field);
        doAction(action, game);
    }

    displayOpenField(&game->field);

    if (game->status == WON)
    {
        printf("Congratulations, you won!\n");
    }
    else
    {
        printf("Sorry, you lost.\n");
    }
}

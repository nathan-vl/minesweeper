#include "tile.h"

char getTileChar(struct Tile *tile)
{
    switch (tile->status)
    {
    case COVERED:
        return COVERED_CHAR;
    case FLAG:
        return FLAG_CHAR;
    case GUESS:
        return GUESS_CHAR;
    default:
        if (tile->hasMine)
        {
            return MINE_CHAR;
        }
        else if (tile->neighbours != 0)
        {
            return tile->neighbours + '0';
        }
    }
    return OPEN_CHAR;
}

char getOpenTileChar(struct Tile *tile)
{
    if (tile->hasMine)
    {
        return MINE_CHAR;
    }
    else if (tile->neighbours != 0)
    {
        return tile->neighbours + '0';
    }

    return OPEN_CHAR;
}

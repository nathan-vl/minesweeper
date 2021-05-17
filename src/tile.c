#include "tile.h"

char getTileChar(struct Tile *tile)
{
    switch (tile->status)
    {
    case covered:
        return COVERED;
    case flag:
        return FLAG;
    case guess:
        return GUESS;
    default:
        if (tile->hasMine)
        {
            return MINE;
        }
        else if (tile->neighbours != 0)
        {
            return tile->neighbours + '0';
        }
    }
    return OPENED;
}

char getOpenTileChar(struct Tile *tile)
{
    if (tile->hasMine)
    {
        return MINE;
    }
    else if (tile->neighbours != 0)
    {
        return tile->neighbours + '0';
    }

    return OPENED;
}

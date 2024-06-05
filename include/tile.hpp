#pragma once

enum class TileStatus
{
    OPEN,
    FLAG,
    COVERED,
    GUESS
};

struct Tiles
{
    bool *mines;
    short *neighbours;
    TileStatus *status;
};

#include "minefield.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>

struct Field newField(const struct Pos size, const int mines)
{
    struct Field field;

    field.mines = mines;
    field.size = size;

    int field_area = size.x * size.y;

    field.tiles = malloc(sizeof(struct Tile) * field_area);

    for (int i = 0; i < field_area; i++)
    {
        struct Tile *tile = &field.tiles[i];
        tile->status = COVERED;
        tile->hasMine = false;
    }

    return field;
}

void destroyField(struct Field *field)
{
    free(field->tiles);
}

struct Tile *getTile(struct Field *field, const struct Pos pos)
{
    return &field->tiles[pos.x + pos.y * field->size.x];
}

bool isInBound(struct Field *field, const struct Pos pos)
{
    bool isInBoundX = pos.x >= 0 && pos.x < field->size.x;
    bool isInBoundY = pos.y >= 0 && pos.y < field->size.y;
    return isInBoundX && isInBoundY;
}

int getNumNeighoursMines(struct Field *field, struct Pos pos)
{
    int total = 0;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if (!(x == 0 && y == 0))
            {
                struct Pos neighbourPos = newPos(pos.x + x, pos.y + y);

                if (isInBound(field, neighbourPos))
                {
                    total += getTile(field, neighbourPos)->hasMine;
                }
            }
        }
    }

    return total;
}

void insertMines(struct Field *field)
{
    int insertedMines = 0;

    for (int i = 0; i < field->size.x * field->size.y; i++)
    {
        struct Tile *tile = &field->tiles[i];

        if (insertedMines == field->mines)
        {
            return;
        }

        if (tile->status != OPEN)
        {
            tile->hasMine = true;
            insertedMines++;
        }
    }
}

void swapTiles(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            struct Tile *currentTile = getTile(field, newPos(x, y));
            if (currentTile->status != OPEN)
            {
                struct Pos pos = randomPos(newPos(
                    field->size.x - 1,
                    field->size.y - 1));

                struct Tile *randomTile = getTile(field, pos);

                if (!((pos.x == x && pos.y == y) || getTile(field, pos)->status == OPEN))
                {
                    struct Tile *temp = currentTile;
                    *currentTile = *randomTile;
                    *randomTile = *temp;
                }
            }
        }
    }
}

void setNeighboursField(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            struct Pos pos = {x, y};
            struct Tile *tile = getTile(field, pos);
            tile->neighbours = getNumNeighoursMines(field, pos);
        }
    }
}

void initMines(struct Field *field)
{
    insertMines(field);
    swapTiles(field);
    setNeighboursField(field);
}

void openNeighboursTiles(struct Field *field, const struct Pos pos)
{
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            struct Pos neighbourPos = newPos(pos.x + x, pos.y + y);

            if (isInBound(field, neighbourPos))
            {
                if (getTile(field, neighbourPos)->status != OPEN)
                {
                    openTile(field, neighbourPos);
                }
            }
        }
    }
}

struct Tile *openTile(struct Field *field, const struct Pos pos)
{
    struct Tile *tile = getTile(field, pos);

    tile->status = OPEN;

    if (!tile->hasMine)
    {
        if (tile->neighbours == 0)
        {
            openNeighboursTiles(field, pos);
        }
    }

    return tile;
}

void openFirstTile(struct Field *field, const struct Pos pos)
{
    getTile(field, pos)->status = OPEN;

    initMines(field);
    openTile(field, pos);
}

void displayField(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            struct Pos pos = newPos(x, y);
            printf("%c", getTileChar(getTile(field, pos)));
        }
        printf("\n");
    }
}

void displayOpenField(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            struct Pos pos = newPos(x, y);
            printf("%c", getOpenTileChar(getTile(field, pos)));
        }
        printf("\n");
    }
}

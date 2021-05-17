#include "minefield.h"
#include "tile.h"
#include <stdlib.h>
#include <stdio.h>

struct Field newField(const struct Pos size, const int mines)
{
    struct Field field;

    field.mines = mines;
    field.size = size;

    field.tiles = malloc(sizeof(struct Tile *) * size.y);

    for (int y = 0; y < size.y; y++)
    {
        field.tiles[y] = malloc(sizeof(struct Tile) * size.x);

        for (int x = 0; x < size.x; x++)
        {
            field.tiles[y][x].status = covered;
            field.tiles[y][x].hasMine = false;
        }
    }

    return field;
}

void destroyField(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        free(field->tiles[y]);
    }
    free(field->tiles);
}

struct Tile *getTile(struct Field *field, const struct Pos pos)
{
    return &field->tiles[pos.y][pos.x];
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
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            struct Tile *tile = getTile(field, newPos(x, y));

            if (insertedMines == field->mines)
            {
                return;
            }

            if (tile->status != opened)
            {
                field->tiles[y][x].hasMine = true;
                insertedMines++;
            }
        }
    }
}

void swapTiles(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            if (getTile(field, newPos(x, y))->status != opened)
            {
                struct Pos pos = randPos(newPos(
                    field->size.x - 1,
                    field->size.y - 1));

                if (!((pos.x == x && pos.y == y) || getTile(field, pos)->status == opened))
                {
                    struct Tile temp = field->tiles[y][x];
                    field->tiles[y][x] = field->tiles[pos.y][pos.x];
                    field->tiles[pos.y][pos.x] = temp;
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

void setOpen(struct Tile *tile)
{
    tile->status = opened;
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
                if (getTile(field, neighbourPos)->status != opened)
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

    setOpen(tile);

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
    setOpen(getTile(field, pos));

    initMines(field);
    openTile(field, pos);
}

void displayField(struct Field *field)
{
    for (int y = 0; y < field->size.y; y++)
    {
        for (int x = 0; x < field->size.x; x++)
        {
            printf("%c", getTileChar(&field->tiles[y][x]));
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
            printf("%c", getOpenTileChar(&field->tiles[y][x]));
        }
        printf("\n");
    }
}

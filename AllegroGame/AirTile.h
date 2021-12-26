#pragma once
#include "Tile.h"
class AirTile :
    public Tile
{
public:
    static const int ID = 0;
    void Draw() const final;
    int GetID() const final;

    bool IsTransparent() const final;
    bool IsEmpty() const final;

    AirTile(World* w, int x, int y);
};


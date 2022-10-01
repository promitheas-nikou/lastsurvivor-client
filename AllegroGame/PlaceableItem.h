#pragma once
#include "UsableItem.h"
#include "Tile.h"

class World;

class PlaceableItem :
    public UsableItem
{
protected:
    PlaceableItem();
public:
    virtual Tile* GetTile(World* w, int x, int y) = 0;
    virtual bool Use(float x, float y, PlayerEntity* p) final;
};


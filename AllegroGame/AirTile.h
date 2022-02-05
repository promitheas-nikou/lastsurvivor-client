#pragma once
#include "Tile.h"
class AirTile :
    public Tile
{
public:
    static const std::string ID;
    void Draw() const final;
    std::string GetID() const final;

    bool IsTransparent() const final;
    bool IsEmpty() const final;

    virtual ~AirTile() = default;
    
    AirTile(World* w, int x, int y);
};


#pragma once
#include "Tile.h"
class AirTile :
    public Tile
{
public:
    static const std::string ID;
    void Draw() const final;
    std::string GetID() const final;

    virtual std::string GetName() const final;

    virtual ToolType GetOptimalToolType() const final;
    virtual int GetMiningResistance() const final;

    virtual Tile* Clone(World* w, int x, int y) const final;

    virtual bool IsTransparent() const final;
    virtual bool IsEmpty() const final;

    virtual ~AirTile() = default;
    
    AirTile(World* w, int x, int y);
};


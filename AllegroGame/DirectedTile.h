#pragma once
#include "Tile.h"

class DirectedTile :
    public Tile
{
protected:
    Direction direction;
public:

    DirectedTile(World* w, int x, int y);
    DirectedTile(World* w, int x, int y, Direction d);

    virtual Direction GetDirection() const final;
    virtual void SerializeToStream(std::ostream& file);
    virtual void DeserializeFromStream(std::istream& file);
};


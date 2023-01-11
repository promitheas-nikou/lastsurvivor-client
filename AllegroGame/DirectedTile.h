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
    virtual void WriteAdditionalDataToFile(std::ofstream& file);
    virtual void LoadAdditionalDataFromFile(std::ifstream& file);
};


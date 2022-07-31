#pragma once
#include "Item.h"

class FuelItem :
    public Item
{
public:

    virtual float GetBurnTime() const = 0;
    virtual float GetBurnHeat() const = 0;

    FuelItem(std::string name, std::string description);

    virtual void DrawItemDetailsPane(int x, int y) override;

};


#pragma once
#include "Item.h"

class FuelItem :
    public Item
{
public:

    virtual float GetBurnTime() const = 0;

    FuelItem(std::string name);

};


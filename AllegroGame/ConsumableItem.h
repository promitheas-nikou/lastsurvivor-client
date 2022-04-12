#pragma once
#include "Consumable.h"
#include "Item.h"

class ConsumableItem :
    public virtual Consumable,
    public Item
{
public:
    ConsumableItem(std::string name);
    virtual ~ConsumableItem() = default;
};


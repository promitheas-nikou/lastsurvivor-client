#pragma once
#include "Consumable.h"
#include "Item.h"
#include "UsableItem.h"

class ConsumableItem :
    public virtual Consumable,
    public UsableItem
{
public:
    ConsumableItem(std::string name);
    virtual ~ConsumableItem() = default;
};


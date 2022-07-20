#pragma once
#include "Consumable.h"
#include "Item.h"
#include "UsableItem.h"

class ConsumableItem :
    public virtual Consumable,
    public UsableItem
{
public:
    ConsumableItem(std::string name, std::string description);

    virtual void DrawItemDetailsPane(int x, int y) override;

    virtual ~ConsumableItem() = default;
};


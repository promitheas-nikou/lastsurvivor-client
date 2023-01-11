#pragma once
#include "Consumable.h"
#include "Item.h"
#include "UsableItem.h"

class ConsumableItem :
    public virtual Consumable,
    public virtual Item
{
public:
    ConsumableItem();

    virtual void DrawItemDetailsPane(int x, int y) override;

    virtual ~ConsumableItem() = default;
};


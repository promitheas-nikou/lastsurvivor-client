#pragma once


#include "ItemInventoryStorageSlotUIComponent.h"
#include "ConsumableItem.h"

class SimpleItemInventoryConsumableStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;
    SimpleItemInventoryConsumableStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryConsumableStorageSlotUIComponent() = default;
};


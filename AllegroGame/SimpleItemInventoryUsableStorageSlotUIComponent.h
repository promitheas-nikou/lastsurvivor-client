#pragma once

#include "ItemInventoryStorageSlotUIComponent.h"
#include "Item.h"
#include "UsableItem.h"

class SimpleItemInventoryUsableStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryUsableStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryUsableStorageSlotUIComponent() = default;
};


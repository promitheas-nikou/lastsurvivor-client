#pragma once

#include "ItemInventoryStorageSlotUIComponent.h"
#include "Item.h"
#include "UsableItem.h"

class SimpleItemInventoryPlaceableStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryPlaceableStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryPlaceableStorageSlotUIComponent() = default;
};
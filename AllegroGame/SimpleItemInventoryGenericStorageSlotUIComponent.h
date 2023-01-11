#pragma once

#include "ItemInventoryStorageSlotUIComponent.h"
#include "Item.h"

class SimpleItemInventoryGenericStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryGenericStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryGenericStorageSlotUIComponent() = default;
};


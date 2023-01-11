#pragma once


#include "ItemInventoryStorageSlotUIComponent.h"
#include "Item.h"

class SimpleItemInventoryFuelStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryFuelStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryFuelStorageSlotUIComponent() = default;
};


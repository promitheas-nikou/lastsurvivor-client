#pragma once
#include "ItemInventoryStorageSlotUIComponent.h"


class SimpleItemInventoryShovelToolStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryShovelToolStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryShovelToolStorageSlotUIComponent() = default;
};


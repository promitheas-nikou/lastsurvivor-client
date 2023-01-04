#pragma once
#include "ItemInventoryStorageSlotUIComponent.h"


class SimpleItemInventoryPickaxeToolStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryPickaxeToolStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryPickaxeToolStorageSlotUIComponent() = default;
};


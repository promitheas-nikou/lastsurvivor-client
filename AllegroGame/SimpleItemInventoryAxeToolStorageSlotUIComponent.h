#pragma once
#include "ItemInventoryStorageSlotUIComponent.h"


class SimpleItemInventoryAxeToolStorageSlotUIComponent :
    public ItemInventoryStorageSlotUIComponent
{
public:
    virtual bool ItemCheckPredicate() const final;

    SimpleItemInventoryAxeToolStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryAxeToolStorageSlotUIComponent() = default;
};


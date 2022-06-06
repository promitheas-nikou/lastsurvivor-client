#pragma once
#include "ItemInventorySlotUIComponent.h"
class SimpleItemInventoryGenericStorageSlotUIComponent :
    public ItemInventorySlotUIComponent
{
protected:

    virtual bool CheckCanSwap() const final;

public:

    SimpleItemInventoryGenericStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryGenericStorageSlotUIComponent() = default;
};


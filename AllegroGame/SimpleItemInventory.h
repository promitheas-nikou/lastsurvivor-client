#pragma once
#include "ItemInventory.h"
class SimpleItemInventory :
    public ItemInventory
{
protected:
    Item** items;
    int size;
public:
    Item** GetItemPtr(int itemID) override;
    Item* GetItem(int itemID) const override;
    void SetItem(int itemID, Item* item) override;

    int GetSize() const override;

    virtual void OverrideFromFile(std::istream& file) final;

    SimpleItemInventory(int size);

    virtual ~SimpleItemInventory();
};


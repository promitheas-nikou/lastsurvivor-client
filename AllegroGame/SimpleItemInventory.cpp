#include "SimpleItemInventory.h"

Item** SimpleItemInventory::GetItemPtr(int itemID)
{
    return &items[itemID];
}

Item* SimpleItemInventory::GetItem(int itemID) const
{
    return items[itemID];
}

void SimpleItemInventory::SetItem(int itemID, Item* item)
{
    items[itemID] = item;
}

int SimpleItemInventory::GetSize() const
{
    return size;
}

SimpleItemInventory::SimpleItemInventory(int size) : size{ size }
{
    items = (Item**)malloc(sizeof(Item*) * size);
    for (int i = 0; i < size; i++)
        items[i] = nullptr;
}

SimpleItemInventory::~SimpleItemInventory()
{
    free(items);
}

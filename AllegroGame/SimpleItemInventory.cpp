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

void SimpleItemInventory::OverrideFromFile(std::istream& file)
{
    uint32_t v;
    file.read(reinterpret_cast<char*>(&v), sizeof(uint32_t));
    if (v <= size)
    {
        for (int i = 0; i < v; i++)
        {
            items[i] = Item::LoadFromFile(file);
        }
        for (int i = v; i < size; i++)
            items[i] = nullptr;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            items[i] = Item::LoadFromFile(file);
        }
        for(int i=size;i<v;i++)
            delete Item::LoadFromFile(file);
    }
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

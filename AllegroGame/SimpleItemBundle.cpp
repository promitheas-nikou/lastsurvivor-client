#include "SimpleItemBundle.h"

void SimpleItemBundle::AddItem(Item* item)
{
    items.push_back(item);
}

ItemBundle* SimpleItemBundle::Clone() const
{
    return new SimpleItemBundle(*this);
}

ItemBundle* SimpleItemBundle::AddToInventory(ItemInventory* inv)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i] == nullptr)
            continue;
        items[i] = inv->AddItem(items[i]);
    }
    return this;
}

void SimpleItemBundle::AddConstToInventory(ItemInventory* inv) const
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i] == nullptr)
            continue;
        inv->AddConstItem(items[i]);
    }
}

Item* SimpleItemBundle::GetItem(int i) const
{
    return items[i];
}

int SimpleItemBundle::GetSize() const
{
    return items.size();
}

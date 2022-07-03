#include "SimpleConstItemBundle.h"
#include "ItemInventory.h"

ConstItemBundle* SimpleConstItemBundle::Clone() const
{
    return new SimpleConstItemBundle(*this);
}

void SimpleConstItemBundle::AddConstToInventory(ItemInventory* inv) const
{
    for (const Item* item : items)
        inv->AddConstItem(item);
}

void SimpleConstItemBundle::AddItem(const Item* item)
{
    items.push_back(item);
}

const Item* SimpleConstItemBundle::GetItem(int i) const
{
    return items[i];
}

int SimpleConstItemBundle::GetSize() const
{
    return items.size();
}

SimpleConstItemBundle* SimpleConstItemBundle::CreateFromJSON(nlohmann::json data)
{
    SimpleConstItemBundle* b = new SimpleConstItemBundle();
    for (nlohmann::json item : data["items"])
        b->AddItem(MakeItemFromJSON(item));
    return b;
}

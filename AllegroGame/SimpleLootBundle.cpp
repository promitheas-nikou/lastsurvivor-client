#include "SimpleLootBundle.h"
#include "SimpleItemBundle.h"

void SimpleLootBundle::AddLootObject(LootObject* obj)
{
    objects.push_back(obj);
}

LootBundle* SimpleLootBundle::Clone() const
{
    return new SimpleLootBundle(*this);
}

void SimpleLootBundle::AddConstToInventory(ItemInventory* inv) const
{
    for (const LootObject* o : objects)
        o->AddConstToInventory(inv);
}

ItemBundle* SimpleLootBundle::ConstCollapseToItemBundle() const
{
    SimpleItemBundle* b = new SimpleItemBundle();
    for (LootObject* o : objects)
        b->AddItemBundle(o->ConstCollapseToItemBundle());
    return b;
}

LootBundle* SimpleLootBundle::CreateFromJSON(nlohmann::json data)
{
    return nullptr;
}

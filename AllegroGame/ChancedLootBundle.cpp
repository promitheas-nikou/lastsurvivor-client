#include "ChancedLootBundle.h"
#include "SimpleItemBundle.h"
#include <cmath>

ChancedLootBundle::ChancedLootObject::ChancedLootObject(LootObject* o, float c) : object{ o }, chance{ c }
{}

void ChancedLootBundle::ChancedLootObject::AddConstToInventory(ItemInventory* inv) const
{
	if ((rand() % 100000) / 100000.f <= chance)
		object->AddConstToInventory(inv);
}

ItemBundle* ChancedLootBundle::ChancedLootObject::CollapseToItemBundle() const
{
	if ((rand() % 100000) / 100000.f > chance)
		return nullptr;
	return object->ConstCollapseToItemBundle();
}

void ChancedLootBundle::AddChancedLootObject(LootObject* obj, float chance)
{
	objects.push_back(ChancedLootObject(obj, chance));
}

LootBundle* ChancedLootBundle::Clone() const
{
	return new ChancedLootBundle(*this);
}

void ChancedLootBundle::AddConstToInventory(ItemInventory* inv) const
{
	for (const ChancedLootObject& i : objects)
		i.AddConstToInventory(inv);
}

ItemBundle* ChancedLootBundle::ConstCollapseToItemBundle() const
{
	SimpleItemBundle* b = new SimpleItemBundle();
	for (const ChancedLootObject& i : objects)
		b->AddItemBundle(i.CollapseToItemBundle());
	return b;
}

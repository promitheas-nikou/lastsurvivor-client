#include "WeightedLootBundle.h"
#include "SimpleItemBundle.h"

void WeightedLootBundle::WeightedLootObject::AddConstToInventory(ItemInventory* inv) const
{
	object->AddConstToInventory(inv);
}

int WeightedLootBundle::WeightedLootObject::GetWeight() const
{
	return weight;
}

LootObject* WeightedLootBundle::WeightedLootObject::GetLootObject() const
{
	return object;
}

WeightedLootBundle::WeightedLootObject::WeightedLootObject(LootObject* o, int w) : object{ o }, weight{ w }
{}

void WeightedLootBundle::AddWeightedLootObject(LootObject* loot, int weight)
{
	objects.push_back(WeightedLootObject(loot, weight));
	totalWeight += weight;
}

LootBundle* WeightedLootBundle::Clone() const
{
	return new WeightedLootBundle(*this);
}

void WeightedLootBundle::AddConstToInventory(ItemInventory* inv) const
{
	int sel = rand() % (totalWeight+1);
	for (const WeightedLootObject& i : objects)
	{
		sel -= i.GetWeight();
		if (sel <= 0)
		{
			i.AddConstToInventory(inv);
			break;
		}
	}
	return;
}

ItemBundle* WeightedLootBundle::ConstCollapseToItemBundle() const
{
	int sel = rand() % (totalWeight+1);
	for (const WeightedLootObject& i : objects)
	{
		sel -= i.GetWeight();
		if (sel <= 0)
		{
			return i.GetLootObject()->ConstCollapseToItemBundle();
		}
	}
	return nullptr;
}

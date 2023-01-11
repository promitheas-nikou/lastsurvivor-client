#pragma once
class ItemInventory;
class ItemBundle;

class LootObject
{
public:
	virtual void AddConstToInventory(ItemInventory*) const = 0;

	virtual ItemBundle* ConstCollapseToItemBundle() const = 0;

	virtual ~LootObject() = default;
};


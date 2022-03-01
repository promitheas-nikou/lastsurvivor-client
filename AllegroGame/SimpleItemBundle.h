#pragma once
#include "ItemBundle.h"
#include "ItemInventory.h"
#include <vector>

class SimpleItemBundle:
	public ItemBundle
{
protected:
	std::vector<Item*> items;
public:
	virtual ItemBundle* Clone() const override;
	virtual ItemBundle* AddToInventory(ItemInventory* inv) override;
	virtual void AddConstToInventory(ItemInventory* inv) const override;
	virtual void AddItem(Item* item) override;
	virtual const Item* GetItem(int i) const override;
	virtual int GetSize() const override;
	SimpleItemBundle() = default;
	SimpleItemBundle(const SimpleItemBundle&) = default;

	static SimpleItemBundle* CreateFromJSON(nlohmann::json data);
};


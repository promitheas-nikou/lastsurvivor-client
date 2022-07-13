#pragma once
#include "LootBundle.h"
class SimpleLootBundle :
    public LootBundle
{
private:
    std::vector<LootObject*> objects;

	void AddLootObject(LootObject* obj);
public:

	virtual LootBundle* Clone() const final;
	virtual void AddConstToInventory(ItemInventory* inv) const final;
	virtual ItemBundle* ConstCollapseToItemBundle() const final;

	static LootBundle* CreateFromJSON(nlohmann::json data);

	SimpleLootBundle() = default;
	SimpleLootBundle(const SimpleLootBundle&) = default;

	virtual ~SimpleLootBundle() = default;

	friend LootBundle;
};


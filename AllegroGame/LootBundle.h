#pragma once
#include "ItemInventory.h"
#include "json.h"
#include "LootObject.h"

class LootBundle:
	public LootObject
{
public:
	virtual LootBundle* Clone() const = 0;

	virtual void AddConstToInventory(ItemInventory* inv) const = 0;

	virtual ItemBundle* ConstCollapseToItemBundle() const = 0;

	static LootBundle* CreateFromJSON(nlohmann::json data);

	virtual ~LootBundle() = default;
};


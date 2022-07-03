#pragma once
#include "ConstItemBundle.h"
#include <vector>
#include "json.h"

class SimpleConstItemBundle :
    public ConstItemBundle
{
protected:
	std::vector<const Item*> items;
public:
	virtual ConstItemBundle* Clone() const override;
	virtual void AddConstToInventory(ItemInventory* inv) const override;
	virtual void AddItem(const Item* item) override;
	virtual const Item* GetItem(int i) const override;
	virtual int GetSize() const override;
	SimpleConstItemBundle() = default;
	SimpleConstItemBundle(const SimpleConstItemBundle&) = default;

	static SimpleConstItemBundle* CreateFromJSON(nlohmann::json data);
};


#pragma once
#include "LootObject.h"
#include "Item.h"
class ItemInventory;
class VariableAmountItem :
    public LootObject
{
private:
    int minAmount;
    int maxAmount;
    std::string id;
public:
    virtual void AddConstToInventory(ItemInventory*) const final;

    virtual ItemBundle* ConstCollapseToItemBundle() const final;

    VariableAmountItem(int min, int max, std::string id);

    static VariableAmountItem* CreateFromJSON(nlohmann::json data);
};


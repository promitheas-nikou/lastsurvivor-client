#include "VariableAmountItem.h"
#include "ItemInventory.h"
#include "SimpleItemBundle.h"

void VariableAmountItem::AddConstToInventory(ItemInventory* inv) const
{
	int newAmount = minAmount + (rand() % (maxAmount - minAmount));
	delete inv->AddItem(MakeItemFromID(id)->SetAmount(newAmount));
}

ItemBundle* VariableAmountItem::ConstCollapseToItemBundle() const
{
	int newAmount = minAmount + (rand() % (maxAmount - minAmount + 1));
	SimpleItemBundle* b = new SimpleItemBundle();
	b->AddItem(MakeItemFromID(id)->SetAmount(newAmount));
	return b;
}

VariableAmountItem::VariableAmountItem(int min, int max, std::string id) : minAmount{ min }, maxAmount{ max }, id{ id }
{}

VariableAmountItem* VariableAmountItem::CreateFromJSON(nlohmann::json data)
{
	return new VariableAmountItem(data["minamount"], data["maxamount"], data["id"]);
}

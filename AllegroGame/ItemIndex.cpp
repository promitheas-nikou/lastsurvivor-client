#include "ItemIndex.h"

const std::unordered_map<std::string, int>& ItemIndex::GetIndexTable() const
{
	return index;
}

bool ItemIndex::CheckGreaterThan(const ItemIndex* ind) const
{
	for (const std::pair<std::string, int> &p : ind->index)
		if (index.at(p.first) < p.second)
			return false;
	return true;
}

ItemIndex::ItemIndex(const ItemInventory* inventory)
{
	Item* tmp;
	for (int i = 0; i < inventory->GetSize(); i++)
	{
		tmp = inventory->GetItem(i);
		if (tmp != nullptr)
			index[tmp->GetID()] += tmp->GetAmount();
	}
}

ItemIndex::ItemIndex(const ItemBundle* bundle)
{
	const Item* tmp;
	for (int i = 0; i < bundle->GetSize(); i++)
	{
		tmp = bundle->GetItem(i);
		if (tmp != nullptr)
			index[tmp->GetID()] += tmp->GetAmount();
	}
}

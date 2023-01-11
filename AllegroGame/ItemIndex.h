#pragma once
#include <unordered_map>
#include <string>
#include "ItemInventory.h"
#include "ItemBundle.h"

class ItemIndex
{
private:
	std::unordered_map<std::string, int> index;

public:

	const std::unordered_map<std::string, int>& GetIndexTable() const;

	bool CheckGreaterThan(const ItemIndex* ind) const;
	int GetMaxFactor(const ItemIndex* ind) const;

	ItemIndex(const ItemInventory* inventory);
	ItemIndex(const ItemBundle* bundle);
	ItemIndex();
};


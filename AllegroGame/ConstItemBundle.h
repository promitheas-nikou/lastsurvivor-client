#pragma once

class ItemInventory;
class Item;

class ConstItemBundle
{
public:
	virtual ConstItemBundle* Clone() const = 0;
	virtual void AddConstToInventory(ItemInventory* inv) const = 0;
	virtual void AddItem(const Item* item) = 0;
	virtual int GetSize() const = 0;
	virtual const Item* GetItem(int n) const = 0;

	virtual ~ConstItemBundle() = default;

	friend ItemInventory;
};


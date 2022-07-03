#pragma once

class ItemInventory;
class Item;

class ItemBundle
{
public:
	virtual ItemBundle* Clone() const = 0;
	virtual ItemBundle* AddToInventory(ItemInventory* inv) = 0;
	virtual void AddConstToInventory(ItemInventory* inv) const = 0;
	virtual void AddItem(Item* item) = 0;
	virtual int GetSize() const = 0;
	virtual Item* GetItem(int n) const = 0;

	virtual ~ItemBundle() = default;

	friend ItemInventory;
};


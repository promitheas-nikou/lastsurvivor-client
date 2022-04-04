#pragma once

#include "Item.h"

class ItemBundle;

class ItemInventory
{
public:

	virtual Item* GetItem(int itemID) const = 0;
	virtual void SetItem(int itemID, Item* item) = 0;
	virtual int AddItemToSlot(Item* item, int itemID);
	virtual void AddConstItem(const Item* item);
	virtual Item* AddItem(Item* item);
	virtual void AddConstItemBundle(const ItemBundle* bundle);
	virtual bool ContainsItem(const Item* item) const;
	virtual bool ContainsItemBundleItems(const ItemBundle* bundle) const;
	virtual void RemoveConstItem(const Item* item);
	virtual void RemoveConstItemBundle(const ItemBundle* bundle);
	virtual ItemBundle* AddItemBundle(ItemBundle* bundle);
	virtual int GetSize() const = 0;
	
	virtual ~ItemInventory() = default;
};



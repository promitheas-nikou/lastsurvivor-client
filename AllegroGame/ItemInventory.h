#pragma once

#include "Item.h"

class ItemInventory
{
public:

	virtual Item* GetItem(int itemID) const = 0;
	virtual void SetItem(int itemID, Item* item) = 0;
	virtual int AddItemToSlot(Item* item, int itemID);
	virtual Item* AddItem(Item* item);
	virtual int GetSize() const = 0;
	
	virtual ~ItemInventory() = default;
};



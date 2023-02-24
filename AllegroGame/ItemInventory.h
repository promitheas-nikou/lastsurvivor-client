#pragma once

#include "Item.h"

class ItemBundle;
class ItemIndex;

class ItemInventory
{
public:

	virtual Item** GetItemPtr(int itemID) = 0;
	virtual Item* GetItem(int itemID) const = 0;
	virtual void SetItem(int itemID, Item* item) = 0;
	virtual int AddItemToSlot(Item* item, int itemID);
	virtual void AddConstItem(const Item* item);
	virtual bool CanAddConstItem(const Item* item);
	virtual Item* AddItem(Item* item);
	virtual void AddConstItemBundle(const ItemBundle* bundle);
	virtual bool ContainsItem(const Item* item) const;
	virtual bool ContainsItemBundleItems(const ItemBundle* bundle) const;
	virtual bool ContainsItemIndexItems(const ItemIndex* bundle) const;
	virtual int CountTimesContainsItem(const Item* item) const;
	virtual int CountTimesContainsItemBundleItems(const ItemBundle* bundle) const;
	virtual void RemoveConstItem(const Item* item);
	virtual void RemoveConstItemBundle(const ItemBundle* bundle);
	virtual ItemBundle* AddItemBundle(ItemBundle* bundle);
	virtual Item* PullItem();
	virtual int GetSize() const = 0;
	virtual void SaveToFile(std::ostream& file);
	static ItemInventory* LoadFromFile(std::istream& file);
	virtual void OverrideFromFile(std::istream& file) = 0;
	
	virtual ~ItemInventory() = default;
};



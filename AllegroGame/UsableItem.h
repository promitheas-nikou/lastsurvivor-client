#pragma once
#include "Usable.h"
#include "Item.h"

class UsableItem:
	public virtual Usable,
	public Item
{
public:

	UsableItem(std::string n, std::string d);

	virtual ~UsableItem() = default;
};


#pragma once
#include "Usable.h"
#include "Item.h"

class UsableItem:
	public virtual Usable,
	public virtual Item
{
public:

	UsableItem();

	virtual ~UsableItem() = 0;
};


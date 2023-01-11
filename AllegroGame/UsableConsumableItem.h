#pragma once
#include "UsableItem.h"
#include "ConsumableItem.h"

class UsableConsumableItem:
	public UsableItem,
	public ConsumableItem
{
public:
	UsableConsumableItem();

	virtual ~UsableConsumableItem();
};


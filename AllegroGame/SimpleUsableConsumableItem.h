#pragma once
#include "UsableConsumableItem.h"
#include "SimpleConsumableItem.h"

class SimpleUsableConsumableItem:
	public UsableConsumableItem,
	public SimpleConsumableItem
{
public:
	SimpleUsableConsumableItem(float health, float hunger, float water);

	virtual ~SimpleUsableConsumableItem() = 0;
};


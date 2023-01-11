#pragma once
#include "ConsumableItem.h"
#include "SimpleConsumable.h"

class SimpleConsumableItem :
    public ConsumableItem,
    public SimpleConsumable
{
public:
    SimpleConsumableItem(float health, float hunger, float water);
    virtual ~SimpleConsumableItem() = 0;
};


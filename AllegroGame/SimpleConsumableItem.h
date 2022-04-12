#pragma once
#include "ConsumableItem.h"
#include "SimpleConsumable.h"

class SimpleConsumableItem :
    public ConsumableItem,
    public SimpleConsumable
{
public:
    SimpleConsumableItem(std::string name, float health, float hunger, float water);
    virtual ~SimpleConsumableItem() = default;
};


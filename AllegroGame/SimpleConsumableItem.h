#pragma once
#include "ConsumableItem.h"
#include "SimpleConsumable.h"

class SimpleConsumableItem :
    public ConsumableItem,
    public SimpleConsumable
{
public:
    SimpleConsumableItem(std::string name, std::string description, float health, float hunger, float water);
    virtual ~SimpleConsumableItem() = default;
};


#include "SimpleConsumableItem.h"

SimpleConsumableItem::SimpleConsumableItem(std::string name, float health, float hunger, float water): ConsumableItem(name), SimpleConsumable(health, hunger, water)
{}

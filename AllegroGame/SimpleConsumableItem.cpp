#include "SimpleConsumableItem.h"

SimpleConsumableItem::SimpleConsumableItem(std::string name, std::string description, float health, float hunger, float water): ConsumableItem(name, description), SimpleConsumable(health, hunger, water)
{}

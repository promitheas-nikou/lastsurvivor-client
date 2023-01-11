#include "SimpleConsumable.h"

SimpleConsumable::SimpleConsumable(float h, float f, float w) : health{ h }, food{ f }, water{ w }
{}

float SimpleConsumable::GetHealthBoost() const
{
    return health;
}

float SimpleConsumable::GetFoodBoost() const
{
    return food;
}

float SimpleConsumable::GetWaterBoost() const
{
    return water;
}

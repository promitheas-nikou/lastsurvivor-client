#pragma once
#include "Usable.h"
class Consumable
{
protected:
	Consumable() = default;
public:

	virtual void Consume(float xpos, float ypos, PlayerEntity* player);

	virtual float GetHealthBoost() const = 0;
	virtual float GetFoodBoost() const = 0;
	virtual float GetWaterBoost() const = 0;

	virtual ~Consumable() = default;
};


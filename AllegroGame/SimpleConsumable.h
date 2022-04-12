#pragma once
#include "Consumable.h"

class SimpleConsumable:
    public virtual Consumable
{
private:
	float health;
	float food;
	float water;
public:
	SimpleConsumable(float h, float f, float w);

	virtual float GetHealthBoost() const final;
	virtual float GetFoodBoost() const final;
	virtual float GetWaterBoost() const final;

	virtual ~SimpleConsumable() = default;
};


#pragma once
#include "Usable.h"
class Consumable:
	public virtual Usable
{
protected:
	Consumable() = default;
public:

	virtual void Use(float xpos, float ypos, PlayerEntity* player) override;

	virtual float GetHealthBoost() const = 0;
	virtual float GetFoodBoost() const = 0;
	virtual float GetWaterBoost() const = 0;

	virtual ~Consumable() = default;
};


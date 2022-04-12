#pragma once
class Consumable
{
public:
	Consumable() = default;

	virtual float GetHealthBoost() const = 0;
	virtual float GetFoodBoost() const = 0;
	virtual float GetWaterBoost() const = 0;

	virtual ~Consumable() = default;
};


#pragma once
class MeleeWeapon
{
private:
public:
	virtual float GetDamage() const = 0;
	virtual float GetRangeSQ() const = 0;
};


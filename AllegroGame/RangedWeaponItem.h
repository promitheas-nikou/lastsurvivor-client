#pragma once
#include "Item.h"
#include "RangedWeapon.h"

class RangedWeaponItem:
	public Item,
	public RangedWeapon
{
protected:
	RangedWeaponItem(std::string name);
};


#pragma once
#include "Item.h"
#include <functional>
#include "RangedWeapon.h"

class RangedWeaponItem:
	public Item,
	public RangedWeapon
{
protected:
	RangedWeaponItem(std::string name);
};


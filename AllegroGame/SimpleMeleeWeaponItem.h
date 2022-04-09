#pragma once
#include "MeleeWeaponItem.h"
#include "SimpleMeleeWeapon.h"


class SimpleMeleeWeaponItem:
	public MeleeWeaponItem,
	public SimpleMeleeWeapon
{
public:

	SimpleMeleeWeaponItem(std::string name, float dmg);

	virtual ~SimpleMeleeWeaponItem() = default;
};


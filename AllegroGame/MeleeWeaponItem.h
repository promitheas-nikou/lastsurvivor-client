#pragma once
#include "MeleeWeapon.h"
#include "Item.h"

class MeleeWeaponItem :
    public virtual MeleeWeapon,
    public Item
{
protected:

    MeleeWeaponItem(std::string name);

    virtual ~MeleeWeaponItem() = default;
};


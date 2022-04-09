#pragma once
#include "MeleeWeapon.h"
class SimpleMeleeWeapon :
    public virtual MeleeWeapon
{
private:
    float damage;
protected:
    void SetDamage(float dmg);
public:
    SimpleMeleeWeapon(float dmg);

    virtual float GetDamage() const final;
};


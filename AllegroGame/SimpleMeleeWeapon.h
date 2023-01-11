#pragma once
#include "MeleeWeapon.h"
class SimpleMeleeWeapon :
    public virtual MeleeWeapon
{
private:
    float damage;
    float range;
protected:
    void SetDamage(float dmg);
    void SetRangeSQ(float rng);
public:
    SimpleMeleeWeapon(float dmg, float rng);

    virtual float GetDamage() const final;
    virtual float GetRangeSQ() const final;
};


#pragma once
#include "Entity.h"
class Projectile :
    public Entity
{
protected:
    Projectile(World* w, float x, float y, float velx, float vely);
    Projectile(World* w, float x, float y, float velx, float vely, float rotation);

    void DoDamage(float damage) const override;
    void DoDamage(MeleeWeapon* weapon) const override;

    virtual ~Projectile() = default;
};


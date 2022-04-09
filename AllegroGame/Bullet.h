#pragma once
#include "Projectile.h"

class Bullet :
    public Projectile
{
private:
    float damage;
    Entity* owner;
public:
    Bullet(World* w, float dmg, float x, float y, float velx, float vely);
    void Tick() override;
    
    void SetOwnerEntity(Entity* entity);

    virtual ~Bullet() = default;
};


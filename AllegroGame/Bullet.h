#pragma once
#include "Projectile.h"

class Bullet :
    public Projectile
{
private:
    Entity* owner;
protected:
    virtual void CollisionCallback(Entity* e);
public:
    Bullet(World* w, float x, float y, float velx, float vely);
    void Tick() override;
    
    virtual float GetDamage() const = 0;

    void SetOwnerEntity(Entity* entity);

    virtual ~Bullet() = default;
};


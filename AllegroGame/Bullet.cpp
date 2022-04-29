#include "Bullet.h"
#include "World.h"
#include "MathUtils.h"

void Bullet::CollisionCallback(Entity* e)
{}

Bullet::Bullet(World* w, float x, float y, float velx, float vely): Projectile(w, x, y, velx, vely)
{}

void Bullet::Tick()
{
    if (this->IsDead())
        return;
    warpRelative(getXvel(), getYvel());
    if (!(
        containingWorld->GetTile(util_floor(GetXpos() - GetXsize() / 2), util_floor(GetYpos() - GetYsize() / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(GetXpos() + GetXsize() / 2), util_floor(GetYpos() - GetYsize() / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(GetXpos() - GetXsize() / 2), util_floor(GetYpos() + GetYsize() / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(GetXpos() + GetXsize() / 2), util_floor(GetYpos() + GetYsize() / 2))->CanWalkThrough()))
    {
        this->PlaySound(SoundType::PROJECTILE_HIT);
        Kill();
    }
	Entity* e = containingWorld->GetEntityColliding(this, this);
    if ((e != nullptr) && (e != owner))
    {
        e->DoDamage(GetDamage());
        e->applyForce(getMass() * getXvel(), getMass() * getYvel());
        CollisionCallback(e);
        this->PlaySound(SoundType::PROJECTILE_HIT);
        Kill();
    }
}

void Bullet::SetOwnerEntity(Entity* entity)
{
    owner = entity;
}

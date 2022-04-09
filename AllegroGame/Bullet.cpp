#include "Bullet.h"
#include "World.h"
#include "MathUtils.h"

Bullet::Bullet(World* w, float dmg, float x, float y, float velx, float vely): damage{dmg},Projectile(w, x, y, velx, vely)
{}

void Bullet::Tick()
{
    if (this->IsDead())
        return;
    warpRelative(getXvel(), getYvel());
    if (!(
        containingWorld->GetTile(util_floor(GetXpos() - getXsize() / 2), util_floor(GetYpos() - getYsize() / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(GetXpos() + getXsize() / 2), util_floor(GetYpos() - getYsize() / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(GetXpos() - getXsize() / 2), util_floor(GetYpos() + getYsize() / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(GetXpos() + getXsize() / 2), util_floor(GetYpos() + getYsize() / 2))->canWalkThrough()))
    {
        Kill();
    }
	Entity* e = containingWorld->GetEntityAtPos(GetXpos(), GetYpos(), this);
    if ((e != nullptr) && (e != owner))
    {
        e->DoDamage(damage);
        Kill();
    }
}

void Bullet::SetOwnerEntity(Entity* entity)
{
    owner = entity;
}

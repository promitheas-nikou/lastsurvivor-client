#include "Projectile.h"

Projectile::Projectile(World* w, float x, float y, float velx, float vely): Entity(w, x, y, 100, 1, velx,vely, .25f, .25f)
{}
Projectile::Projectile(World* w, float x, float y, float velx, float vely, float rot): Entity(w, x, y, 100, 1, velx,vely, .25f, .25f)
{
	SetRotation(rot);
}

void Projectile::DoDamage(float damage) const
{}

void Projectile::DoDamage(MeleeWeapon* weapon) const
{}

#include "SimpleMeleeWeapon.h"

void SimpleMeleeWeapon::SetDamage(float dmg)
{
	damage = dmg;
}

void SimpleMeleeWeapon::SetRangeSQ(float rng)
{
	range = rng;
}

SimpleMeleeWeapon::SimpleMeleeWeapon(float dmg, float rng) : damage{ dmg }, range{ rng }, MeleeWeapon()
{}

float SimpleMeleeWeapon::GetDamage() const
{
	return damage;
}

float SimpleMeleeWeapon::GetRangeSQ() const
{
	return range;
}

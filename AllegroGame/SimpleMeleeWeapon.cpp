#include "SimpleMeleeWeapon.h"

void SimpleMeleeWeapon::SetDamage(float dmg)
{
	damage = dmg;
}

SimpleMeleeWeapon::SimpleMeleeWeapon(float dmg) : damage{ dmg }, MeleeWeapon()
{}

float SimpleMeleeWeapon::GetDamage() const
{
	return damage;
}

#include "RangedWeapon.h"

void RangedWeapon::SetCollisionCallback(std::function<void(Entity*)> c)
{
	callback = c;
}

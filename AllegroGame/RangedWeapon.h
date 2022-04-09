#pragma once
class World;
class Entity;

class RangedWeapon
{
public:
	virtual void Fire(World* world, float xpos, float ypos, float rot, Entity* owner = nullptr) = 0;

	virtual ~RangedWeapon() = default;
};


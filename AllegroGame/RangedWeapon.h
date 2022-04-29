#pragma once
class World;
class Entity;
#include <functional>

class RangedWeapon
{
protected:
	std::function<void(Entity*)> callback;
public:
	virtual void Fire(World* world, float xpos, float ypos, float rot, Entity* owner = nullptr) = 0;

	void SetCollisionCallback(std::function<void(Entity*)> c);
	virtual ~RangedWeapon() = default;
};


#pragma once

#include <string>

class World;
class WorldChunk;

class Entity
{
private:
	std::string name;
	float xpos;
	float ypos;

	bool dead = false;

	float health;
	static const float MIN_HEALTH;

protected:
	World* containingWorld;

public:

	float getXpos() const;
	float getYpos() const;

	void applyForce(float dx, float dy); //TODO
	void setSpeed(float dx, float dy); //TODO

	void warpAbsolute(float x, float y);
	void warpRelative(float dx, float dy);

	virtual void Draw() = 0;

	virtual void Tick();

	virtual std::string getName() const;
	virtual bool shouldBeRemoved() const;

	Entity(World* w);

	friend WorldChunk;
	friend World;
};


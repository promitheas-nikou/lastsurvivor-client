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

public:

	float getXpos() const;
	float getYpos() const;

	virtual std::string getName() const;
	virtual bool shouldBeRemoved() const;


	friend WorldChunk;
	friend World;
};


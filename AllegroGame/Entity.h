#pragma once

#include <string>
#include <allegro5/allegro5.h>

class World;
class WorldChunk;

class Entity
{
private:

	std::string name;

	bool dead = false;

	float xpos;
	float ypos;
	float xvel;
	float yvel;
	float mass;
	float xsize;
	float ysize;
	float rotation;
	float health;
	static const float MIN_HEALTH;

protected:
	World* containingWorld;

public:

	float getXpos() const;
	float getYpos() const;
	float getXvel() const;
	float getYvel() const;
	float getXsize() const;
	float getYsize() const;
	float getRotation() const;

	void applyForce(float dx, float dy);
	void setSpeed(float dx, float dy);

	void rotateTo(float targetRotation);

	void warpAbsolute(float x, float y);
	void warpRelative(float dx, float dy);

	virtual void Draw() = 0;

	virtual void Tick();

	virtual std::string getName() const;
	virtual bool shouldBeRemoved() const;

	virtual float getFriction() const;

	Entity(World* w, float xpos, float ypos, float mass, float initialVelocityX, float initialVelocityY);
	Entity(World* w, float xpos, float ypos, float mass);
	Entity(World* w, float xpos, float ypos);

	virtual ~Entity() = default;

	friend WorldChunk;
	friend World;
};


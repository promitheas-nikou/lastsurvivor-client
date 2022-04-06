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
	mutable float health;
	float maxHealth;

protected:
	World* containingWorld;

	void SetRotation(float rot);

public:

	float GetXpos() const;
	float GetYpos() const;
	float getXvel() const;
	float getYvel() const;
	float getXsize() const;
	float getYsize() const;
	float getRotation() const;

	virtual bool IsHostile() const;
	virtual bool IsPassive() const;

	int GetHealth() const;

	void applyForce(float dx, float dy);
	void setSpeed(float dx, float dy);

	void rotateTo(float targetRotation);

	void warpAbsolute(float x, float y);
	void warpRelative(float dx, float dy);

	virtual void Draw() = 0;

	virtual void Tick();

	virtual std::string getName() const;
	virtual bool shouldBeRemoved() const;

	virtual void DoDamage(float dmg) const;

	virtual float getFriction() const;

	Entity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY);
	Entity(World* w, float xpos, float ypos, float maxHealth, float mass);
	Entity(World* w, float xpos, float ypos, float maxHealth);

	virtual ~Entity() = default;

	friend WorldChunk;
	friend World;
};


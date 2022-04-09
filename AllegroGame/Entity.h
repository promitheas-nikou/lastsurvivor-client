#pragma once

#include <string>
#include <allegro5/allegro5.h>
#include "MeleeWeapon.h"

class World;
class WorldChunk;
class PlayerEntity;

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
	float xsize = .5f;
	float ysize = .5f;
	float rotation;
	mutable float health;
	float maxHealth;
	bool bounce = false;
	bool hasFriction = true;

protected:
	World* containingWorld;

	void SetRotation(float rot);

	void SetName(std::string n);

	void SetShouldBounce(bool b);

	void SetHasFriction(bool b);

	void Revive();
	void Kill();

	void SetHealth(float health);

public:

	float GetXpos() const;
	float GetYpos() const;
	float getXvel() const;
	float getYvel() const;
	float getXsize() const;
	float getYsize() const;
	float getRotation() const;

	bool DoesBounce() const;

	bool GetHasFriction() const;

	virtual bool ContainsPos(float x, float y);
	
	virtual bool IsHostile() const;
	virtual bool IsPassive() const;

	float GetHealth() const;
	float GetMaxHealth() const;

	void applyForce(float dx, float dy);
	void setSpeed(float dx, float dy);

	void rotateTo(float targetRotation);

	void warpAbsolute(float x, float y);
	void warpRelative(float dx, float dy);

	virtual void Draw() = 0;

	virtual void Tick();

	virtual std::string GetName() const;
	virtual std::string GetID() const = 0;
	virtual bool IsDead() const;

	virtual void DoDamage(MeleeWeapon* w) const;
	virtual void DoDamage(float dmg) const;

	virtual float getFriction() const;

	Entity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY, float xs, float ys);
	Entity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY);
	Entity(World* w, float xpos, float ypos, float maxHealth, float mass);
	Entity(World* w, float xpos, float ypos, float maxHealth);

	virtual ~Entity() = default;

	friend WorldChunk;
	friend World;
	friend PlayerEntity;
};


#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <allegro5/allegro5.h>
#include "MeleeWeapon.h"
#include "SoundType.h"

class World;
class WorldChunk;
class PlayerEntity;
class ItemBundle;

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
	bool killOnCollision = false;

protected:
	World* containingWorld;

	void SetRotation(float rot);

	void SetName(std::string n);

	void SetShouldBounce(bool b);

	void SetHasFriction(bool b);

	bool GetKillOnCollision() const;

	void SetKillOnCollision(bool b);

	void Revive();
	void Kill();

	void SetHealth(float health);

public:

	static const float MAXIMUM_IGNORABLE_SPEED;

	virtual Entity* Clone(World* world, float x, float y) const = 0;

	float GetXpos() const;
	float GetYpos() const;
	float GetXvel() const;
	float GetYvel() const;
	float GetXsize() const;
	float GetYsize() const;
	float GetRotation() const;
	float GetMass() const;
	World* GetContainingWorld() const;

	bool DoesBounce() const;

	bool GetHasFriction() const;

	virtual bool ContainsPos(float x, float y);
	virtual bool IntersectRect(float x1, float y1, float x2, float y2);
	
	virtual bool CollidesWith(Entity* e) const;

	virtual void DeserializeFromStream(std::istream& file);
	virtual void SerializeToStream(std::ostream& file);

	virtual bool IsHostile() const;
	virtual bool IsPassive() const;

	float GetHealth() const;
	float GetMaxHealth() const;

	void ApplyForce(float dx, float dy);
	void ApplyForceRotated(float f);
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
	virtual void Heal(float hl) const;

	virtual float getFriction() const;

	virtual void PlaySound(SoundType st) const;

	virtual ItemBundle* GetKillingDrops() const;

	Entity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY, float xs, float ys);
	Entity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY);
	Entity(World* w, float xpos, float ypos, float maxHealth, float mass);
	Entity(World* w, float xpos, float ypos, float maxHealth);

	virtual ~Entity() = default;

	friend WorldChunk;
	friend World;
	friend PlayerEntity;
	friend class Consumable;
	friend class LuaInterface;
};


extern std::unordered_map<std::string, const Entity*> prototype_entities;

Entity* MakeEntity(World* world, std::string id, float x, float y);


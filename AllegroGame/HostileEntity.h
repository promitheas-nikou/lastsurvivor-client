#pragma once
#include "Entity.h"
class HostileEntity :
    public Entity
{
private:
	int damageCooldown = 0;
protected:
    virtual bool IsHostile() const final;
	virtual void Tick() override;

	virtual void LoadAdditionalDataFromFile(std::ifstream& file);
	virtual void WriteAdditionalDataToFile(std::ofstream& file);

	bool CooldownReady() const;
	void ResetCooldown(int val);

	HostileEntity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY, float xs, float ys);
	HostileEntity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY);
	HostileEntity(World* w, float xpos, float ypos, float maxHealth, float mass);
	HostileEntity(World* w, float xpos, float ypos, float maxHealth);
};


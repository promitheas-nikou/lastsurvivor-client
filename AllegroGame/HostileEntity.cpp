#include "HostileEntity.h"

bool HostileEntity::IsHostile() const
{
    return true;
}

void HostileEntity::Tick()
{
    Entity::Tick();
    damageCooldown--;
}

bool HostileEntity::CooldownReady() const
{
    return damageCooldown<=0;
}

void HostileEntity::ResetCooldown(int val)
{
    damageCooldown = val;
}

HostileEntity::HostileEntity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY): Entity(w, xpos, ypos, maxHealth, mass, initialVelocityX, initialVelocityY)
{}

HostileEntity::HostileEntity(World * w, float xpos, float ypos, float maxHealth, float mass): Entity(w, xpos, ypos, maxHealth, mass)
{}

HostileEntity::HostileEntity(World * w, float xpos, float ypos, float maxHealth): Entity(w, xpos, ypos, maxHealth)
{}

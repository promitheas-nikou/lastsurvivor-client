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

void HostileEntity::LoadAdditionalDataFromFile(std::ifstream& file)
{
    Entity::LoadAdditionalDataFromFile(file);
    file.read(reinterpret_cast<char*>(&damageCooldown), sizeof(int));
}

void HostileEntity::WriteAdditionalDataToFile(std::ofstream& file)
{
    Entity::WriteAdditionalDataToFile(file);
    file.write(reinterpret_cast<char*>(&damageCooldown), sizeof(int));
}

bool HostileEntity::CooldownReady() const
{
    return damageCooldown<=0;
}

void HostileEntity::ResetCooldown(int val)
{
    damageCooldown = val;
}

HostileEntity::HostileEntity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY, float xs, float ys) : Entity(w, xpos, ypos, maxHealth, mass, initialVelocityX, initialVelocityY, xs, ys)
{}

HostileEntity::HostileEntity(World* w, float xpos, float ypos, float maxHealth, float mass, float initialVelocityX, float initialVelocityY): Entity(w, xpos, ypos, maxHealth, mass, initialVelocityX, initialVelocityY)
{}

HostileEntity::HostileEntity(World * w, float xpos, float ypos, float maxHealth, float mass): Entity(w, xpos, ypos, maxHealth, mass)
{}

HostileEntity::HostileEntity(World * w, float xpos, float ypos, float maxHealth): Entity(w, xpos, ypos, maxHealth)
{}

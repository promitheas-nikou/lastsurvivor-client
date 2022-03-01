#include "HostileEntity.h"

bool HostileEntity::IsHostile() const
{
    return true;
}

HostileEntity::HostileEntity(World* w, float xpos, float ypos, float mass, float initialVelocityX, float initialVelocityY): Entity(w, xpos, ypos, mass, initialVelocityX, initialVelocityY)
{}

HostileEntity::HostileEntity(World * w, float xpos, float ypos, float mass): Entity(w, xpos, ypos, mass)
{}

HostileEntity::HostileEntity(World * w, float xpos, float ypos): Entity(w, xpos, ypos)
{}

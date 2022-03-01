#pragma once
#include "Entity.h"
class HostileEntity :
    public Entity
{

protected:
    virtual bool IsHostile() const final;
	HostileEntity(World* w, float xpos, float ypos, float mass, float initialVelocityX, float initialVelocityY);
	HostileEntity(World* w, float xpos, float ypos, float mass);
	HostileEntity(World* w, float xpos, float ypos);
};


#pragma once
#include "HostileEntity.h"

class SimpleHostileEntity :
    public HostileEntity
{
private:
    float speed = .05f;
public:
    virtual void Tick() override;
    virtual void Draw() override;

    SimpleHostileEntity(World* world, float xpos, float ypos);
};


#pragma once
#include "HostileEntity.h"

class ZombieEntity :
    public HostileEntity
{
private:
    float speed = .0005f;
    float reach = 0.4f;
public:
    virtual void Tick() override;
    virtual void Draw() override;

    ZombieEntity(World* world, float xpos, float ypos);
};


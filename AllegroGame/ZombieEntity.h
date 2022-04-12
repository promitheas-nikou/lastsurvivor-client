#pragma once
#include "HostileEntity.h"

class ZombieEntity :
    public HostileEntity
{
private:
    float speed = .0075f;
    float reach = 0.4f;
    static const std::string ID;
public:
    virtual void Tick() override;
    virtual void Draw() override;
    virtual std::string GetID() const final;

    ZombieEntity(World* world, float xpos, float ypos);
};


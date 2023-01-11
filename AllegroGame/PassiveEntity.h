#pragma once
#include "Entity.h"

class PassiveEntity :
    public Entity
{
private:
    enum PassiveEntityState {WANDER, PASSIVE};
    PassiveEntityState state;
    float targetRotation;
    uint16_t timeLeft;
protected:
    virtual void OnPassiveStateStart();
    virtual void OnPassiveStateEnd();
    virtual void OnWanderStateStart();
    virtual void OnWanderStateEnd();

    uint16_t minTime = 50;
    uint16_t maxTime = 200;
    float forceApplied = .05;
public:
    virtual void Tick() override;

    PassiveEntity(World* world, float xpos, float ypos, float maxHealth);
    PassiveEntity(World* world, float xpos, float ypos, float maxHealth, float mass);
    PassiveEntity(World* world, float xpos, float ypos, float maxHealth, float mass, float initialVelX, float initialVelY);

};


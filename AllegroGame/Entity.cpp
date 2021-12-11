#include "Entity.h"

const float Entity::MIN_HEALTH = 0.f;

float Entity::getXpos() const
{
    return xpos;
}

float Entity::getYpos() const
{
    return ypos;
}

std::string Entity::getName() const
{
    return name;
}

bool Entity::shouldBeRemoved() const
{
    return dead;
}

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

void Entity::Tick()
{
    return;
}

std::string Entity::getName() const
{
    return name;
}

bool Entity::shouldBeRemoved() const
{
    return dead;
}

Entity::Entity(World* w): containingWorld(w)
{}

void Entity::warpAbsolute(float x, float y)
{
    xpos = x;
    ypos = y;
}

void Entity::warpRelative(float dx, float dy)
{
    xpos += dx;
    ypos += dy;
}


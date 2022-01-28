 #include "Entity.h"
#include "World.h"
#define _USE_MATH_DEFINES
#include <math.h>

const float Entity::MIN_HEALTH = 0.f;

float Entity::getXpos() const
{
    return xpos;
}

float Entity::getYpos() const
{
    return ypos;
}

float Entity::getXvel() const
{
    return xvel;
}

float Entity::getYvel() const
{
    return yvel;
}

float Entity::getXsize() const
{
    return xsize;
}

float Entity::getYsize() const
{
    return ysize;
}

float Entity::getRotation() const
{
    return rotation;
}

void Entity::applyForce(float dx, float dy)
{
    xvel += dx / mass;
    yvel += dy / mass;
}

void Entity::setSpeed(float dx, float dy)
{
    xvel = dx;
    yvel = dy;
}

void Entity::Tick()
{
    xpos += xvel;
    ypos += yvel;
    xvel *= getFriction();
    yvel *= getFriction();
}

std::string Entity::getName() const
{
    return name;
}

bool Entity::shouldBeRemoved() const
{
    return dead;
}

float Entity::getFriction() const
{
    return .8f;
}

Entity::Entity(World* w, float x, float y, float mass, float initialVelocityX, float initialVelocityY) : containingWorld{ w }, xpos{ x }, ypos{ y }, mass{ mass }, xvel{ initialVelocityX }, yvel{ initialVelocityY }, health{1.f}
{}

Entity::Entity(World* w, float x, float y, float mass) : Entity(w, x, y, mass, 0, 0)
{}

Entity::Entity(World * w, float xpos, float ypos): Entity(w, xpos, ypos, 1.f)
{}

void Entity::rotateTo(float r)
{
}

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


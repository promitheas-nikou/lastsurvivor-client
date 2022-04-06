#include "Entity.h"
#include "World.h"
#include "MathUtils.h"
#define _USE_MATH_DEFINES
#include <math.h>

void Entity::SetRotation(float rot)
{
    rotation = rot;
}

float Entity::GetXpos() const
{
    return xpos;
}

float Entity::GetYpos() const
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

bool Entity::IsHostile() const
{
    return false;
}

bool Entity::IsPassive() const
{
    return true;
}

int Entity::GetHealth() const
{
    return health;
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
    if (!(
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2))->canWalkThrough()))
    {
        xpos -= xvel;
        xvel = 0;
    }
    else
    {
        xvel *= getFriction()*containingWorld->GetGroundTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->GetFrictionModifier();
    }
    ypos += yvel;
    if (!(
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->canWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2))->canWalkThrough()))
    {
        ypos -= yvel;
        yvel = 0;
    }
    else
    {
        yvel *= getFriction()*containingWorld->GetGroundTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->GetFrictionModifier();
    }
    if (health <= 0)
        dead = true;
}

std::string Entity::getName() const
{
    return name;
}

bool Entity::shouldBeRemoved() const
{
    return dead;
}

void Entity::DoDamage(float dmg) const
{
    health -= dmg;
}

float Entity::getFriction() const
{
    return .8f;
}

Entity::Entity(World* w, float x, float y, float maxHealth, float mass, float initialVelocityX, float initialVelocityY) : containingWorld{ w }, xpos{ x }, ypos{ y }, mass{ mass }, xvel{ initialVelocityX }, yvel{ initialVelocityY }, health{ maxHealth }, maxHealth{ maxHealth }
{}

Entity::Entity(World* w, float x, float y, float maxHealth, float mass) : Entity(w, x, y, maxHealth, mass, 0, 0)
{}

Entity::Entity(World * w, float xpos, float ypos, float maxHealth): Entity(w, xpos, ypos, maxHealth, 1.f)
{}

void Entity::rotateTo(float r)
{
    rotation = r;
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


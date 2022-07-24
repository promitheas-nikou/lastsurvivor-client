#include "Entity.h"
#include "World.h"
#include "MathUtils.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "ResourceLoader.h"

const float Entity::MAXIMUM_IGNORABLE_SPEED = 0.001f;

void Entity::SetRotation(float rot)
{
    rotation = rot;
}

void Entity::SetName(std::string n)
{
    name = n;
}

void Entity::SetShouldBounce(bool b)
{
    bounce = b;
}

void Entity::SetHasFriction(bool b)
{
    hasFriction = b;
}

bool Entity::GetHasFriction() const
{
    return hasFriction;
}

void Entity::Revive()
{
    SetHealth(GetMaxHealth());
    dead = false;
}

void Entity::Kill()
{
    dead = true;
}

void Entity::SetHealth(float health)
{
    Entity::health = health;
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

float Entity::GetXsize() const
{
    return xsize;
}

float Entity::GetYsize() const
{
    return ysize;
}

float Entity::getRotation() const
{
    return rotation;
}

float Entity::getMass() const
{
    return mass;
}

World* Entity::GetContainingWorld() const
{
    return containingWorld;
}

bool Entity::DoesBounce() const
{
    return bounce;
}

bool Entity::ContainsPos(float x, float y)
{
    return (xpos - xsize / 2 <= x) && (x <= xpos + xsize / 2) && (ypos - ysize / 2 <= y) && (y <= ypos + ysize / 2);
}

bool Entity::CollidesWith(Entity* e)
{
    float e1sx = GetXpos() - GetXsize() / 2;
    float e1sy = GetYpos() - GetYsize() / 2;
    float e1ex = GetXpos() + GetXsize() / 2;
    float e1ey = GetYpos() + GetYsize() / 2;
    float e2sx = e->GetXpos() - e->GetXsize() / 2;
    float e2sy = e->GetYpos() - e->GetYsize() / 2;
    float e2ex = e->GetXpos() + e->GetXsize() / 2;
    float e2ey = e->GetYpos() + e->GetYsize() / 2;
    bool cx = (e1sx <= e2sx) ? (e1ex >= e2sx) : (e1sx <= e2ex);
    bool cy = (e1sy <= e2sy) ? (e1ey >= e2sy) : (e1sy <= e2ey);
    return cx && cy;
}

bool Entity::IsHostile() const
{
    return false;
}

bool Entity::IsPassive() const
{
    return true;
}

float Entity::GetHealth() const
{
    return health;
}

float Entity::GetMaxHealth() const
{
    return maxHealth;
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
    if (this->IsDead())
        return;
    xpos += xvel;
    if (!(
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2))->CanWalkThrough()))
    {
        xpos -= xvel;
        xvel = DoesBounce()?-xvel:0;
    }
    else
    {
        if(GetHasFriction())
            xvel *= getFriction()*containingWorld->GetGroundTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->GetFrictionModifier();
    }
    ypos += yvel;
    if (!(
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->CanWalkThrough() &&
        containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2))->CanWalkThrough()))
    {
        ypos -= yvel;
        yvel = DoesBounce() ? -yvel : 0;
    }
    else
    {
        if (GetHasFriction())
            yvel *= getFriction()*containingWorld->GetGroundTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->GetFrictionModifier();
    }
    if (health <= 0)
        dead = true;
    if (abs(xvel) <= MAXIMUM_IGNORABLE_SPEED)
        xvel = 0;
    if (abs(yvel) <= MAXIMUM_IGNORABLE_SPEED)
        yvel = 0;
    if (!IsDead())
        if (xvel || yvel)
        {
            containingWorld->GetGroundTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2))->PlaySound(SoundType::TILE_WALK);
        }
}

std::string Entity::GetName() const
{
    return name;
}

bool Entity::IsDead() const
{
    return dead;
}

void Entity::DoDamage(MeleeWeapon* w) const
{
    DoDamage((w==nullptr)?1:w->GetDamage());
}

void Entity::DoDamage(float dmg) const
{
    this->PlaySound(SoundType::ENTITY_HURT);
    health -= dmg;
}

void Entity::Heal(float hl) const
{
    health = std::min(health + hl, GetMaxHealth());
}

float Entity::getFriction() const
{
    return .8f;
}

void Entity::PlaySound(SoundType st) const
{}

Entity::Entity(World* w, float x, float y, float maxHealth, float mass, float initialVelocityX, float initialVelocityY, float xs, float ys) : containingWorld{ w }, xpos{ x }, ypos{ y }, mass{ mass }, xvel{ initialVelocityX }, yvel{ initialVelocityY }, health{ maxHealth }, maxHealth{ maxHealth }, xsize{ xs }, ysize{ ys }
{}

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

std::unordered_map<std::string, const Entity*> prototype_entities;


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

bool Entity::GetKillOnCollision() const
{
    return killOnCollision;
}

void Entity::SetKillOnCollision(bool b)
{
    killOnCollision = b;
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

float Entity::GetXvel() const
{
    return xvel;
}

float Entity::GetYvel() const
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

float Entity::GetRotation() const
{
    return rotation;
}

float Entity::GetMass() const
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

bool Entity::IntersectRect(float x1, float y1, float x2, float y2)
{
    float x3 = GetXpos() - xsize / 2;
    float x4 = GetXpos() + xsize / 2;
    float y3 = GetYpos() - ysize / 2;
    float y4 = GetYpos() + ysize / 2;
    if (x3 > x2)
        return false;
    if (x4 < x1)
        return false;
    if (y3 > y2)
        return false;
    if (y4 < y1)
        return false;
    return true;
}

bool Entity::CollidesWith(Entity* e) const
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

void Entity::DeserializeFromStream(std::istream& file)
{
    file.read(reinterpret_cast<char*>(&xpos), sizeof(float));
    file.read(reinterpret_cast<char*>(&ypos), sizeof(float));
    file.read(reinterpret_cast<char*>(&xvel), sizeof(float));
    file.read(reinterpret_cast<char*>(&yvel), sizeof(float));
    file.read(reinterpret_cast<char*>(&rotation), sizeof(float));
    file.read(reinterpret_cast<char*>(&health), sizeof(float));
    file.read(reinterpret_cast<char*>(&mass), sizeof(float));
    file.read(reinterpret_cast<char*>(&xsize), sizeof(float));
    file.read(reinterpret_cast<char*>(&ysize), sizeof(float));
}

void Entity::SerializeToStream(std::ostream& file)
{
    file.write(reinterpret_cast<char*>(&xpos), sizeof(float));
    file.write(reinterpret_cast<char*>(&ypos), sizeof(float));
    file.write(reinterpret_cast<char*>(&xvel), sizeof(float));
    file.write(reinterpret_cast<char*>(&yvel), sizeof(float));
    file.write(reinterpret_cast<char*>(&rotation), sizeof(float));
    file.write(reinterpret_cast<char*>(&health), sizeof(float));
    file.write(reinterpret_cast<char*>(&mass), sizeof(float));
    file.write(reinterpret_cast<char*>(&xsize), sizeof(float));
    file.write(reinterpret_cast<char*>(&ysize), sizeof(float));
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

void Entity::ApplyForce(float dx, float dy)
{
    xvel += dx / mass;
    yvel += dy / mass;
}

void Entity::ApplyForceRotated(float f)
{
    ApplyForce(-sinf(-GetRotation()) * f, -cosf(-GetRotation()) * f);
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
    Tile* a = containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2));
    Tile* b = containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2));
    Tile* c = containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2));
    Tile* d = containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2));
    GroundTile* u = containingWorld->GetGroundTile(util_floor(xpos), util_floor(ypos));
    if (u == nullptr)
    {
        Kill();
        return;
    }
    xpos += xvel;
    a = containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2));
    b = containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2));
    c = containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2));
    d = containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2));
    if (!(
        (a == nullptr || a->CanWalkThrough())&&
        (b == nullptr || b->CanWalkThrough()) &&
        (c == nullptr || c->CanWalkThrough()) &&
        (d == nullptr || d->CanWalkThrough())))
    {
        if (killOnCollision)
        {
            PlaySound(SoundType::PROJECTILE_HIT);
            Kill();
            return;
        }
        xpos -= xvel;
        xvel = DoesBounce()?-xvel:0;
    }
    else
    {
        if(GetHasFriction())
            xvel *= 1 - getFriction()*u->GetFrictionModifier();
    }
    ypos += yvel;
    a = containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos - ysize / 2));
    b = containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos - ysize / 2));
    c = containingWorld->GetTile(util_floor(xpos - xsize / 2), util_floor(ypos + ysize / 2));
    d = containingWorld->GetTile(util_floor(xpos + xsize / 2), util_floor(ypos + ysize / 2));
    if (!(
        (a == nullptr || a->CanWalkThrough()) &&
        (b == nullptr || b->CanWalkThrough()) &&
        (c == nullptr || c->CanWalkThrough()) &&
        (d == nullptr || d->CanWalkThrough())))
    {
        if (killOnCollision)
        {
            PlaySound(SoundType::PROJECTILE_HIT);
            Kill();
            return;
        }
        ypos -= yvel;
        yvel = DoesBounce() ? -yvel : 0;
    }
    else
    {
        if (GetHasFriction())
            yvel *= 1 - getFriction() * u->GetFrictionModifier();
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
            u->PlaySound(SoundType::TILE_WALK);
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
    return .5f;
}

void Entity::PlaySound(SoundType st) const
{}

ItemBundle* Entity::GetKillingDrops() const
{
    return nullptr;
}

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

Entity* MakeEntity(World* world, std::string id, float x, float y)
{
    const Entity* e= prototype_entities[id];
    if (e == nullptr)
        return nullptr;
    return e->Clone(world, x, y);
}
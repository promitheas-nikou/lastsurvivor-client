#pragma once
#include "Item.h"

class PlayerEntity;

class Usable
{
public:

    virtual void Use(float xpos, float ypos, PlayerEntity* player) = 0;

    virtual ~Usable() = default;
};


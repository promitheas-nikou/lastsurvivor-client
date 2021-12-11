#pragma once
#include "Entity.h"
class PlayerEntity :
    public Entity
{

	friend WorldChunk;
	friend World;
};


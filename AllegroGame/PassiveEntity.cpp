#include "PassiveEntity.h"
#define _USE_MATH_DEFINES
#include <math.h>

void PassiveEntity::OnPassiveStateStart()
{}

void PassiveEntity::OnPassiveStateEnd()
{}

void PassiveEntity::OnWanderStateStart()
{}

void PassiveEntity::OnWanderStateEnd()
{}

void PassiveEntity::Tick()
{
	Entity::Tick();
	if (timeLeft <= 0) {
		switch (state) {
		case WANDER:
			state = PASSIVE;
			break;
		case PASSIVE:
			SetRotation(((rand() % 10000) / M_PI)*2);
			state = WANDER;
			break;
		}
		timeLeft = minTime + (rand() % (maxTime - minTime));
	}
	else
	{
		switch (state) {
		case WANDER:
			Entity::ApplyForceRotated(forceApplied);
			break;
		case PASSIVE:
			break;
		}
		timeLeft--;
	}
}

PassiveEntity::PassiveEntity(World* world, float xpos, float ypos, float maxHealth) : Entity(world, xpos, ypos, maxHealth), state{ PASSIVE }, timeLeft{ 0 }
{}

PassiveEntity::PassiveEntity(World* world, float xpos, float ypos, float maxHealth, float mass) : Entity(world, xpos, ypos, maxHealth, mass), state{ PASSIVE }, timeLeft{ 0 }
{}

PassiveEntity::PassiveEntity(World* world, float xpos, float ypos, float maxHealth, float mass, float initialVelX, float initialVelY) : Entity(world, xpos, ypos, maxHealth, mass, initialVelX, initialVelY), state{ PASSIVE }, timeLeft{ 0 }
{}

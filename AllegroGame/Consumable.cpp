#include "Consumable.h"
#include "PlayerEntity.h"

void Consumable::Consume(float xpos, float ypos, PlayerEntity* player)
{
	player->health += GetHealthBoost();
	player->hunger += GetFoodBoost();
	player->water += GetWaterBoost();
}

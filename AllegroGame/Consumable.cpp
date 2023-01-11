#include "Consumable.h"
#include "PlayerEntity.h"

bool Consumable::Consume(float xpos, float ypos, PlayerEntity* player)
{
	player->health = std::min(player->health+GetHealthBoost(),player->GetMaxHealth());
	player->hunger = std::min(player->hunger + GetFoodBoost(), player->MAX_HUNGER);
	player->water = std::min(player->water + GetWaterBoost(), player->MAX_WATER);
	return true;
}

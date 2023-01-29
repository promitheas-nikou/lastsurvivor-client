#include "CookedCowMeatItem.h"
#include "ResourceLoader.h"

std::string CookedCowMeatItem::NAME;
std::string CookedCowMeatItem::DESCRIPTION;
ALLEGRO_BITMAP* CookedCowMeatItem::TEXTURE;
const std::string CookedCowMeatItem::ID = "items.cow_meat_cooked";
float CookedCowMeatItem::HEALTH;
float CookedCowMeatItem::HUNGER;
float CookedCowMeatItem::WATER;

std::string CookedCowMeatItem::GetID() const
{
	return ID;
}

CookedCowMeatItem::CookedCowMeatItem(): Item(NAME, DESCRIPTION)
{}

Item* CookedCowMeatItem::Clone() const
{
	return new CookedCowMeatItem(*this);
}

float CookedCowMeatItem::GetHealthBoost() const
{
	return HEALTH;
}

float CookedCowMeatItem::GetFoodBoost() const
{
	return HUNGER;
}

float CookedCowMeatItem::GetWaterBoost() const
{
	return WATER;
}

void CookedCowMeatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void CookedCowMeatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}


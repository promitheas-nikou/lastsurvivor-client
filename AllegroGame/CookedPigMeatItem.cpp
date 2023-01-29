#include "CookedPigMeatItem.h"
#include "ResourceLoader.h"

std::string CookedPigMeatItem::NAME;
std::string CookedPigMeatItem::DESCRIPTION;
ALLEGRO_BITMAP* CookedPigMeatItem::TEXTURE;
const std::string CookedPigMeatItem::ID = "items.pig_meat_cooked";
float CookedPigMeatItem::HEALTH;
float CookedPigMeatItem::HUNGER;
float CookedPigMeatItem::WATER;

std::string CookedPigMeatItem::GetID() const
{
	return ID;
}

CookedPigMeatItem::CookedPigMeatItem(): Item(NAME, DESCRIPTION)
{}

Item* CookedPigMeatItem::Clone() const
{
	return new CookedPigMeatItem(*this);
}

float CookedPigMeatItem::GetHealthBoost() const
{
	return HEALTH;
}

float CookedPigMeatItem::GetFoodBoost() const
{
	return HUNGER;
}

float CookedPigMeatItem::GetWaterBoost() const
{
	return WATER;
}

void CookedPigMeatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void CookedPigMeatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}


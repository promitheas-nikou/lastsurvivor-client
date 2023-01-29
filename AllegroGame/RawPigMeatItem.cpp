#include "RawPigMeatItem.h"
#include "ResourceLoader.h"

std::string RawPigMeatItem::NAME;
std::string RawPigMeatItem::DESCRIPTION;
ALLEGRO_BITMAP* RawPigMeatItem::TEXTURE;
const std::string RawPigMeatItem::ID = "items.pig_meat_raw";
float RawPigMeatItem::HEALTH;
float RawPigMeatItem::HUNGER;
float RawPigMeatItem::WATER;

std::string RawPigMeatItem::GetID() const
{
	return ID;
}

RawPigMeatItem::RawPigMeatItem(): Item(NAME, DESCRIPTION)
{}

Item* RawPigMeatItem::Clone() const
{
	return new RawPigMeatItem(*this);
}

float RawPigMeatItem::GetHealthBoost() const
{
	return HEALTH;
}

float RawPigMeatItem::GetFoodBoost() const
{
	return HUNGER;
}

float RawPigMeatItem::GetWaterBoost() const
{
	return WATER;
}

void RawPigMeatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void RawPigMeatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}


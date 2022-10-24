#include "RawCowMeatItem.h"
#include "ResourceLoader.h"

std::string RawCowMeatItem::NAME;
std::string RawCowMeatItem::DESCRIPTION;
ALLEGRO_BITMAP* RawCowMeatItem::TEXTURE;
const std::string RawCowMeatItem::ID = "items.cow_meat_raw";
float RawCowMeatItem::HEALTH;
float RawCowMeatItem::HUNGER;
float RawCowMeatItem::WATER;

std::string RawCowMeatItem::GetID() const
{
	return ID;
}

RawCowMeatItem::RawCowMeatItem(): Item(NAME, DESCRIPTION)
{}

Item* RawCowMeatItem::Clone() const
{
	return new RawCowMeatItem(*this);
}

float RawCowMeatItem::GetHealthBoost() const
{
	return HEALTH;
}

float RawCowMeatItem::GetFoodBoost() const
{
	return HUNGER;
}

float RawCowMeatItem::GetWaterBoost() const
{
	return WATER;
}

void RawCowMeatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void RawCowMeatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}


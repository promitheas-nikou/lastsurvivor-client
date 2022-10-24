#include "RawSheepMeatItem.h"
#include "ResourceLoader.h"

std::string RawSheepMeatItem::NAME;
std::string RawSheepMeatItem::DESCRIPTION;
ALLEGRO_BITMAP* RawSheepMeatItem::TEXTURE;
const std::string RawSheepMeatItem::ID = "items.sheep_meat_raw";
float RawSheepMeatItem::HEALTH;
float RawSheepMeatItem::HUNGER;
float RawSheepMeatItem::WATER;

std::string RawSheepMeatItem::GetID() const
{
	return ID;
}

RawSheepMeatItem::RawSheepMeatItem(): Item(NAME, DESCRIPTION)
{}

Item* RawSheepMeatItem::Clone() const
{
	return new RawSheepMeatItem(*this);
}

float RawSheepMeatItem::GetHealthBoost() const
{
	return HEALTH;
}

float RawSheepMeatItem::GetFoodBoost() const
{
	return HUNGER;
}

float RawSheepMeatItem::GetWaterBoost() const
{
	return WATER;
}

void RawSheepMeatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void RawSheepMeatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}


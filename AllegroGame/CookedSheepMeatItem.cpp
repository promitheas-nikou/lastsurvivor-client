#include "CookedSheepMeatItem.h"
#include "ResourceLoader.h"

std::string CookedSheepMeatItem::NAME;
std::string CookedSheepMeatItem::DESCRIPTION;
ALLEGRO_BITMAP* CookedSheepMeatItem::TEXTURE;
const std::string CookedSheepMeatItem::ID = "items.sheep_meat_cooked";
float CookedSheepMeatItem::HEALTH;
float CookedSheepMeatItem::HUNGER;
float CookedSheepMeatItem::WATER;

std::string CookedSheepMeatItem::GetID() const
{
	return ID;
}

CookedSheepMeatItem::CookedSheepMeatItem(): Item(NAME, DESCRIPTION)
{}

Item* CookedSheepMeatItem::Clone() const
{
	return new CookedSheepMeatItem(*this);
}

float CookedSheepMeatItem::GetHealthBoost() const
{
	return HEALTH;
}

float CookedSheepMeatItem::GetFoodBoost() const
{
	return HUNGER;
}

float CookedSheepMeatItem::GetWaterBoost() const
{
	return WATER;
}

void CookedSheepMeatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void CookedSheepMeatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}


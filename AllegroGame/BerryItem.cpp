#include "BerryItem.h"
#include "ResourceLoader.h"

std::string BerryItem::NAME;
ALLEGRO_BITMAP* BerryItem::TEXTURE;
const std::string BerryItem::ID = "items.berry";
float BerryItem::HEALTH;
float BerryItem::HUNGER;
float BerryItem::WATER;

std::string BerryItem::GetID() const
{
	return ID;
}

Item* BerryItem::Clone() const
{
	return new BerryItem(*this);
}

BerryItem::BerryItem() : SimpleConsumableItem(NAME, HEALTH, HUNGER, WATER)
{}

void BerryItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void BerryItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
}

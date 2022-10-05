#include "CharcoalItem.h"
#include "ResourceLoader.h"

std::string CharcoalItem::NAME;
std::string CharcoalItem::DESCRIPTION;
ALLEGRO_BITMAP* CharcoalItem::TEXTURE;
float CharcoalItem::BURN_TIME;
float CharcoalItem::BURN_HEAT;
const std::string CharcoalItem::ID = "items.charcoal";

std::string CharcoalItem::GetID() const
{
	return ID;
}

CharcoalItem::CharcoalItem(): FuelItem(NAME, DESCRIPTION)
{}

Item* CharcoalItem::Clone() const
{
	return new CharcoalItem(*this);
}

float CharcoalItem::GetBurnTime() const
{
	return BURN_TIME;
}

float CharcoalItem::GetBurnHeat() const
{
	return BURN_HEAT;
}

void CharcoalItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void CharcoalItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	BURN_TIME = data[DATA_JSON_BURN_TIME_KEY];
	BURN_HEAT = data[DATA_JSON_BURN_HEAT_KEY];
}


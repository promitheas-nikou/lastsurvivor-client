#include "CoalItem.h"
#include "ResourceLoader.h"


std::string CoalItem::NAME;
ALLEGRO_BITMAP* CoalItem::TEXTURE;
float CoalItem::BURN_TIME;
const std::string CoalItem::ID = "items.coal";

std::string CoalItem::GetID() const
{
    return ID;
}

Item* CoalItem::Clone() const
{
	return new CoalItem(*this);
}

float CoalItem::GetBurnTime() const
{
	return BURN_TIME;
}

CoalItem::CoalItem() : FuelItem(NAME)
{}

void CoalItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void CoalItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	BURN_TIME = data[DATA_JSON_BURN_TIME_KEY];
}

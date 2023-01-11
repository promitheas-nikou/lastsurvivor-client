#include "DirtItem.h"
#include "ResourceLoader.h"

std::string DirtItem::NAME;
std::string DirtItem::DESCRIPTION;
ALLEGRO_BITMAP* DirtItem::TEXTURE;
const std::string DirtItem::ID = "items.dirt";

std::string DirtItem::GetID() const
{
	return ID;
}

Item* DirtItem::Clone() const
{
	return new DirtItem(*this);
}

DirtItem::DirtItem() : Item(NAME, DESCRIPTION)
{}

void DirtItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void DirtItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

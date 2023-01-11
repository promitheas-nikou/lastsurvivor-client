#include "StoneItem.h"
#include "ResourceLoader.h"

std::string StoneItem::NAME;
std::string StoneItem::DESCRIPTION;
ALLEGRO_BITMAP* StoneItem::TEXTURE;
const std::string StoneItem::ID = "items.stone";

std::string StoneItem::GetID() const
{
    return ID;
}

StoneItem::StoneItem(): Item(NAME, DESCRIPTION)
{}

Item* StoneItem::Clone()const
{
	return new StoneItem(*this);
}

void StoneItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void StoneItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

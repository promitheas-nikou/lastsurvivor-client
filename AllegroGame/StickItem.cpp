#include "StickItem.h"
#include "ResourceLoader.h"

std::string StickItem::NAME;
std::string StickItem::DESCRIPTION;
ALLEGRO_BITMAP* StickItem::TEXTURE;
const std::string StickItem::ID = "items.stick";

std::string StickItem::GetID() const
{
    return ID;
}

StickItem::StickItem(): Item(NAME, DESCRIPTION)
{}

Item* StickItem::Clone()const
{
	return new StickItem(*this);
}

void StickItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void StickItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

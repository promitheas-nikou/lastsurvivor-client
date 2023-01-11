#include "CopperIngotItem.h"
#include "ResourceLoader.h"

std::string CopperIngotItem::NAME;
std::string CopperIngotItem::DESCRIPTION;
ALLEGRO_BITMAP* CopperIngotItem::TEXTURE;
const std::string CopperIngotItem::ID = "items.copper_ingot";

std::string CopperIngotItem::GetID() const
{
	return ID;
}

CopperIngotItem::CopperIngotItem(): Item(NAME, DESCRIPTION)
{}

Item* CopperIngotItem::Clone() const
{
	return new CopperIngotItem(*this);
}

void CopperIngotItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void CopperIngotItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}


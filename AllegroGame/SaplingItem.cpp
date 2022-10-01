#include "SaplingItem.h"
#include "ResourceLoader.h"
#include "TreeTile.h"

std::string SaplingItem::NAME;
std::string SaplingItem::DESCRIPTION;
ALLEGRO_BITMAP* SaplingItem::TEXTURE;
const std::string SaplingItem::ID = "items.sapling";

std::string SaplingItem::GetID() const
{
	return ID;
}

Tile* SaplingItem::GetTile(World* w, int x, int y)
{
	return new TreeTile(w,x,y,0);
}

Item* SaplingItem::Clone() const
{
	return new SaplingItem(*this);
}

SaplingItem::SaplingItem() : Item(NAME, DESCRIPTION)
{}

void SaplingItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void SaplingItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

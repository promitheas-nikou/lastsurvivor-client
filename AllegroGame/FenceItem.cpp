#include "FenceItem.h"
#include "ResourceLoader.h"

std::string FenceItem::NAME;
std::string FenceItem::DESCRIPTION;
ALLEGRO_BITMAP* FenceItem::TEXTURE;
const std::string FenceItem::ID = "items.fence";

std::string FenceItem::GetID() const
{
	return ID;
}

Tile* FenceItem::GetTile(World* w, int x, int y)
{
	return MakeTile(w, "tiles.fence", x, y);
}

Item* FenceItem::Clone() const
{
	return new FenceItem(*this);
}

FenceItem::FenceItem() : PlaceableItem(NAME, DESCRIPTION)
{}

void FenceItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void FenceItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

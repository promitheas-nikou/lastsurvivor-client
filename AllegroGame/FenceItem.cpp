#include "FenceItem.h"
#include "ResourceLoader.h"

std::string FenceItem::NAME;
std::string FenceItem::TILE_ID;
std::string FenceItem::DESCRIPTION;
ALLEGRO_BITMAP* FenceItem::TEXTURE;
const std::string FenceItem::ID = "items.fence";

std::string FenceItem::GetID() const
{
	return ID;
}

Tile* FenceItem::GetTile(World* w, int x, int y, Direction d)
{
	return MakeTile(w, TILE_ID, x, y, d);
}

Item* FenceItem::Clone() const
{
	return new FenceItem(*this);
}

FenceItem::FenceItem() : Item(NAME, DESCRIPTION)
{}

void FenceItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void FenceItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TILE_ID = data[DATA_JSON_TILE_ID_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}

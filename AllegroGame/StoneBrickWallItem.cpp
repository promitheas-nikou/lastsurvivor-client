#include "StoneBrickWallItem.h"
#include "ResourceLoader.h"
#include "StoneBrickWallTile.h"

std::string StoneBrickWallItem::NAME;
std::string StoneBrickWallItem::TILE_ID;
std::string StoneBrickWallItem::DESCRIPTION;
ALLEGRO_BITMAP* StoneBrickWallItem::TEXTURE;
const std::string StoneBrickWallItem::ID = "items.stone_brick_wall";

std::string StoneBrickWallItem::GetID() const
{
	return ID;
}

Tile* StoneBrickWallItem::GetTile(World* w, int x, int y, Direction d)
{
	return MakeTile(w, TILE_ID, x, y, d);
}

Item* StoneBrickWallItem::Clone() const
{
	return new StoneBrickWallItem(*this);
}

StoneBrickWallItem::StoneBrickWallItem() : Item(NAME, DESCRIPTION)
{}

void StoneBrickWallItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void StoneBrickWallItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TILE_ID = data[DATA_JSON_TILE_ID_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

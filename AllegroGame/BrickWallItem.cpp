#include "BrickWallItem.h"
#include "ResourceLoader.h"
#include "BrickWallTile.h"

std::string BrickWallItem::NAME;
std::string BrickWallItem::TILE_ID;
std::string BrickWallItem::DESCRIPTION;
ALLEGRO_BITMAP* BrickWallItem::TEXTURE;
const std::string BrickWallItem::ID = "items.brick_wall";

std::string BrickWallItem::GetID() const
{
	return ID;
}

Tile* BrickWallItem::GetTile(World* w, int x, int y, Direction d)
{
	return MakeTile(w, TILE_ID, x, y, d);
}

Item* BrickWallItem::Clone() const
{
	return new BrickWallItem(*this);
}

BrickWallItem::BrickWallItem() : Item(NAME, DESCRIPTION)
{}

void BrickWallItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default",30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void BrickWallItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TILE_ID = data[DATA_JSON_TILE_ID_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}

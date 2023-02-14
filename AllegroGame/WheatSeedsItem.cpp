#include "WheatSeedsItem.h"
#include "ResourceLoader.h"

std::string WheatSeedsItem::NAME;
std::string WheatSeedsItem::DESCRIPTION;
std::string WheatSeedsItem::TILE_ID;
ALLEGRO_BITMAP* WheatSeedsItem::TEXTURE;
const std::string WheatSeedsItem::ID = "items.wheat_seeds";

std::string WheatSeedsItem::GetID() const
{
	return ID;
}

WheatSeedsItem::WheatSeedsItem(): Item(NAME, DESCRIPTION)
{}

Tile* WheatSeedsItem::GetTile(World * w, int xpos, int ypos, Direction d)
{
	return MakeTile(w, TILE_ID, xpos, ypos, d);
}

Item* WheatSeedsItem::Clone() const
{
	return new WheatSeedsItem(*this);
}

void WheatSeedsItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default",30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void WheatSeedsItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	TILE_ID = data[DATA_JSON_TILE_ID_KEY];
}


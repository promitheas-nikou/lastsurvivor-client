#include "TorchItem.h"
#include "ResourceLoader.h"
#include "TorchTile.h"

std::string TorchItem::NAME;
std::string TorchItem::TILE_ID;
std::string TorchItem::DESCRIPTION;
ALLEGRO_BITMAP* TorchItem::TEXTURE;
const std::string TorchItem::ID = "items.torch";

std::string TorchItem::GetID() const
{
	return ID;
}

Tile* TorchItem::GetTile(World* w, int x, int y, Direction d)
{
	return MakeTile(w, TILE_ID, x, y, d);
}

Item* TorchItem::Clone() const
{
	return new TorchItem(*this);
}

TorchItem::TorchItem() : Item(NAME, DESCRIPTION)
{}

void TorchItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void TorchItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TILE_ID = data[DATA_JSON_TILE_ID_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

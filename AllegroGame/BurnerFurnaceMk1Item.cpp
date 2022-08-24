#include "BurnerFurnaceMk1Item.h"
#include "ResourceLoader.h"
#include "BurnerFurnaceMk1Tile.h"

std::string BurnerFurnaceMk1Item::NAME;
std::string BurnerFurnaceMk1Item::DESCRIPTION;
ALLEGRO_BITMAP* BurnerFurnaceMk1Item::TEXTURE;
const std::string BurnerFurnaceMk1Item::ID = "items.burner_furnace_mk1";

std::string BurnerFurnaceMk1Item::GetID() const
{
	return ID;
}

Tile* BurnerFurnaceMk1Item::GetTile(World* w, int x, int y)
{
	return new BurnerFurnaceMk1Tile(w,x,y);
}

Item* BurnerFurnaceMk1Item::Clone() const
{
	return new BurnerFurnaceMk1Item(*this);
}

BurnerFurnaceMk1Item::BurnerFurnaceMk1Item() : PlaceableItem(NAME, DESCRIPTION)
{}

void BurnerFurnaceMk1Item::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void BurnerFurnaceMk1Item::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

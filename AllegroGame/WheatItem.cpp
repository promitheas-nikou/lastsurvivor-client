#include "WheatItem.h"
#include "ResourceLoader.h"

std::string WheatItem::NAME;
std::string WheatItem::DESCRIPTION;
ALLEGRO_BITMAP* WheatItem::TEXTURE;
const std::string WheatItem::ID = "items.wheat";

std::string WheatItem::GetID() const
{
	return ID;
}

WheatItem::WheatItem(): Item(NAME, DESCRIPTION)
{}

Item* WheatItem::Clone() const
{
	return new WheatItem(*this);
}

void WheatItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default",30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void WheatItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}


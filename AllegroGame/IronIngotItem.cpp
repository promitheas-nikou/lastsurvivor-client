#include "IronIngotItem.h"
#include "ResourceLoader.h"

std::string IronIngotItem::NAME;
std::string IronIngotItem::DESCRIPTION;
ALLEGRO_BITMAP* IronIngotItem::TEXTURE;
const std::string IronIngotItem::ID = "items.iron_ingot";

std::string IronIngotItem::GetID() const
{
	return ID;
}

IronIngotItem::IronIngotItem(): Item(NAME, DESCRIPTION)
{}

Item* IronIngotItem::Clone() const
{
	return new IronIngotItem(*this);
}

void IronIngotItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void IronIngotItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}


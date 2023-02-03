#include "SandItem.h"
#include "ResourceLoader.h"

std::string SandItem::NAME;
std::string SandItem::DESCRIPTION;
ALLEGRO_BITMAP* SandItem::TEXTURE;
const std::string SandItem::ID = "items.sand";

std::string SandItem::GetID() const
{
    return ID;
}

SandItem::SandItem(): Item(NAME, DESCRIPTION)
{}

Item* SandItem::Clone() const
{
	return new SandItem(*this);
}

void SandItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void SandItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}

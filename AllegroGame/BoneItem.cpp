#include "BoneItem.h"
#include "ResourceLoader.h"

std::string BoneItem::NAME;
std::string BoneItem::DESCRIPTION;
ALLEGRO_BITMAP* BoneItem::TEXTURE;
const std::string BoneItem::ID = "items.bone";

std::string BoneItem::GetID() const
{
	return ID;
}

BoneItem::BoneItem(): Item(NAME, DESCRIPTION)
{}

Item* BoneItem::Clone() const
{
	return new BoneItem(*this);
}

void BoneItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default",30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void BoneItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}


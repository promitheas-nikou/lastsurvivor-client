#include "WoodenHoeItem.h"
#include "MathUtils.h"
#include "PlayerEntity.h"
#include "World.h"

const std::string WoodenHoeItem::ID = "items.wooden_hoe";
std::string WoodenHoeItem::NAME;
std::string WoodenHoeItem::DESCRIPTION;
ALLEGRO_BITMAP* WoodenHoeItem::TEXTURE;

WoodenHoeItem::WoodenHoeItem() : Item(NAME, DESCRIPTION)
{}

std::string WoodenHoeItem::GetID() const
{
	return ID;
}

bool WoodenHoeItem::Use(float xpos, float ypos, PlayerEntity* player)
{
	int tx = util_floor(xpos);
	int ty = util_floor(ypos);
	player->GetContainingWorld()->GetGroundTile(tx, ty)->Till();
	return false;
}

Item* WoodenHoeItem::Clone() const
{
	return new WoodenHoeItem(*this);
}

void WoodenHoeItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void WoodenHoeItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

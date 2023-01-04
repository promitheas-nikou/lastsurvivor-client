#include "WoodenShovelItem.h"
#include "ResourceLoader.h"

std::string WoodenShovelItem::NAME;
std::string WoodenShovelItem::DESCRIPTION;
ALLEGRO_BITMAP* WoodenShovelItem::TEXTURE;
float WoodenShovelItem::MINING_DAMAGE;
int WoodenShovelItem::MINING_LEVEL;
Tool::ToolType WoodenShovelItem::MINING_TYPE;
const std::string WoodenShovelItem::ID = "items.wooden_shovel";

std::string WoodenShovelItem::GetID() const
{
	return ID;
}

float WoodenShovelItem::GetMiningDamage() const
{
	return MINING_DAMAGE;
}

Tool::ToolType WoodenShovelItem::GetToolType() const
{
	return MINING_TYPE;
}

int WoodenShovelItem::GetMiningLevel() const
{
	return MINING_LEVEL;
}

WoodenShovelItem::WoodenShovelItem() : ToolItem(), Item(NAME, DESCRIPTION)
{}


Item* WoodenShovelItem::Clone()const
{
	return new WoodenShovelItem(*this);
}

void WoodenShovelItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void WoodenShovelItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	MINING_DAMAGE = data[DATA_JSON_MINING_DAMAGE_KEY];
	MINING_LEVEL = data[DATA_JSON_MINING_LEVEL_KEY];
	MINING_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_MINING_TYPE_KEY]);
}

#include "WoodenAxeItem.h"
#include "ResourceLoader.h"

std::string WoodenAxeItem::NAME;
std::string WoodenAxeItem::DESCRIPTION;
ALLEGRO_BITMAP* WoodenAxeItem::TEXTURE;
float WoodenAxeItem::MINING_DAMAGE;
int WoodenAxeItem::MINING_LEVEL;
Tool::ToolType WoodenAxeItem::MINING_TYPE;
const std::string WoodenAxeItem::ID = "items.wooden_axe";

std::string WoodenAxeItem::GetID() const
{
	return ID;
}

float WoodenAxeItem::GetMiningDamage() const
{
	return MINING_DAMAGE;
}

Tool::ToolType WoodenAxeItem::GetToolType() const
{
	return MINING_TYPE;
}

int WoodenAxeItem::GetMiningLevel() const
{
	return MINING_LEVEL;
}

WoodenAxeItem::WoodenAxeItem() : ToolItem(), Item(NAME, DESCRIPTION)
{}


Item* WoodenAxeItem::Clone()const
{
	return new WoodenAxeItem(*this);
}

void WoodenAxeItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void WoodenAxeItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	MINING_DAMAGE = data[DATA_JSON_MINING_DAMAGE_KEY];
	MINING_LEVEL = data[DATA_JSON_MINING_LEVEL_KEY];
	MINING_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_MINING_TYPE_KEY]);
}

#include "WoodenPickaxeItem.h"
#include "ResourceLoader.h"

std::string WoodenPickaxeItem::NAME;
std::string WoodenPickaxeItem::DESCRIPTION;
ALLEGRO_BITMAP* WoodenPickaxeItem::TEXTURE;
float WoodenPickaxeItem::MINING_DAMAGE;
int WoodenPickaxeItem::MINING_LEVEL;
Tool::ToolType WoodenPickaxeItem::MINING_TYPE;
const std::string WoodenPickaxeItem::ID = "items.wooden_pickaxe";

std::string WoodenPickaxeItem::GetID() const
{
	return ID;
}

float WoodenPickaxeItem::GetMiningDamage() const
{
	return MINING_DAMAGE;
}

Tool::ToolType WoodenPickaxeItem::GetToolType() const
{
	return MINING_TYPE;
}

int WoodenPickaxeItem::GetMiningLevel() const
{
	return MINING_LEVEL;
}

WoodenPickaxeItem::WoodenPickaxeItem() : ToolItem(), Item(NAME, DESCRIPTION)
{}


Item* WoodenPickaxeItem::Clone()const
{
	return new WoodenPickaxeItem(*this);
}

void WoodenPickaxeItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void WoodenPickaxeItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	MINING_DAMAGE = data[DATA_JSON_MINING_DAMAGE_KEY];
	MINING_LEVEL = data[DATA_JSON_MINING_LEVEL_KEY];
	MINING_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_MINING_TYPE_KEY]);
}

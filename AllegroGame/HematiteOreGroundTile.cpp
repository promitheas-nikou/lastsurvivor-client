#include "HematiteOreGroundTile.h"
#include "ResourceLoader.h"

std::string HematiteOreGroundTile::NAME;
ALLEGRO_BITMAP* HematiteOreGroundTile::TEXTURE;
int HematiteOreGroundTile::MINING_RESISTANCE;
const LootBundle* HematiteOreGroundTile::DROP;
ToolType HematiteOreGroundTile::TOOL_TYPE;

const std::string HematiteOreGroundTile::ID = "gtiles.hematite_ore";

std::string HematiteOreGroundTile::GetID() const
{
	return ID;
}

HematiteOreGroundTile::HematiteOreGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void HematiteOreGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void HematiteOreGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* HematiteOreGroundTile::Clone(World* w, int x, int y) const
{
	return new HematiteOreGroundTile(w, x, y);
}

const ItemBundle* HematiteOreGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

int HematiteOreGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

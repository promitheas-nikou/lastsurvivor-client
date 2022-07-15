#include "MalachiteOreGroundTile.h"
#include "ResourceLoader.h"

std::string MalachiteOreGroundTile::NAME;
ALLEGRO_BITMAP* MalachiteOreGroundTile::TEXTURE;
int MalachiteOreGroundTile::MINING_RESISTANCE;
const LootBundle* MalachiteOreGroundTile::DROP;
ToolType MalachiteOreGroundTile::TOOL_TYPE;

const std::string MalachiteOreGroundTile::ID = "gtiles.malachite_ore";

std::string MalachiteOreGroundTile::GetID() const
{
	return ID;
}

MalachiteOreGroundTile::MalachiteOreGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void MalachiteOreGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void MalachiteOreGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* MalachiteOreGroundTile::Clone(World* w, int x, int y) const
{
	return new MalachiteOreGroundTile(w, x, y);
}

const ItemBundle* MalachiteOreGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

int MalachiteOreGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

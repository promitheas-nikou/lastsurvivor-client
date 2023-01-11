#include "MagnetiteOreGroundTile.h"
#include "ResourceLoader.h"

std::string MagnetiteOreGroundTile::NAME;
ALLEGRO_BITMAP* MagnetiteOreGroundTile::TEXTURE;
int MagnetiteOreGroundTile::MINING_RESISTANCE;
const LootBundle* MagnetiteOreGroundTile::DROP;
ToolType MagnetiteOreGroundTile::TOOL_TYPE;

const std::string MagnetiteOreGroundTile::ID = "gtiles.magnetite_ore";

std::string MagnetiteOreGroundTile::GetID() const
{
	return ID;
}

MagnetiteOreGroundTile::MagnetiteOreGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void MagnetiteOreGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void MagnetiteOreGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* MagnetiteOreGroundTile::Clone(World* w, int x, int y) const
{
	return new MagnetiteOreGroundTile(w, x, y);
}

const ItemBundle* MagnetiteOreGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

int MagnetiteOreGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

#include "WaterGroundTile.h"
#include "ResourceLoader.h"

std::string WaterGroundTile::NAME;
ALLEGRO_BITMAP* WaterGroundTile::TEXTURE;
const ItemBundle* WaterGroundTile::DROP;
int WaterGroundTile::MINING_RESISTANCE;
ToolType WaterGroundTile::TOOL_TYPE;
const std::string WaterGroundTile::ID = "gtiles.water";

std::string WaterGroundTile::GetID() const
{
	return ID;
}

WaterGroundTile::WaterGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void WaterGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void WaterGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

const ItemBundle* WaterGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP;
}

int WaterGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

float WaterGroundTile::GetFrictionModifier() const
{
    return 0.5f;
}

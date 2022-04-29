#include "SandGroundTile.h"
#include "ResourceLoader.h"

std::string SandGroundTile::NAME;
ALLEGRO_BITMAP* SandGroundTile::TEXTURE;
const ItemBundle* SandGroundTile::DROP;
int SandGroundTile::MINING_RESISTANCE;
ToolType SandGroundTile::TOOL_TYPE;
const std::string SandGroundTile::ID = "gtiles.sand";


std::string SandGroundTile::GetID() const
{
	return ID;
}

SandGroundTile::SandGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void SandGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void SandGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* SandGroundTile::Clone(World* w, int x, int y) const
{
	return new SandGroundTile(w, x, y);
}

const ItemBundle* SandGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP;
}

int SandGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

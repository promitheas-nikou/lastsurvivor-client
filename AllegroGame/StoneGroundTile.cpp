#include "StoneGroundTile.h"
#include "ResourceLoader.h"

std::string StoneGroundTile::NAME;
ALLEGRO_BITMAP* StoneGroundTile::TEXTURE;
int StoneGroundTile::MINING_RESISTANCE;
const ItemBundle* StoneGroundTile::DROP;
ToolType StoneGroundTile::TOOL_TYPE;

const std::string StoneGroundTile::ID = "gtiles.stone";

std::string StoneGroundTile::GetID() const
{
	return ID;
}

StoneGroundTile::StoneGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void StoneGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void StoneGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* StoneGroundTile::Clone(World* w, int x, int y) const
{
	return new StoneGroundTile(w, x, y);
}

const ItemBundle* StoneGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP;
}

int StoneGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

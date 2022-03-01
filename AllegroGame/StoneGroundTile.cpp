#include "StoneGroundTile.h"
#include "ResourceLoader.h"

std::string StoneGroundTile::NAME;
ALLEGRO_BITMAP* StoneGroundTile::TEXTURE;
int StoneGroundTile::MINING_RESISTANCE;
const ItemBundle* StoneGroundTile::DROP;

const std::string StoneGroundTile::ID = "gtiles.stone";

std::string StoneGroundTile::GetID() const
{
	return ID;
}

StoneGroundTile::StoneGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void StoneGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
}

void StoneGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

const ItemBundle* StoneGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP;
}

int StoneGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

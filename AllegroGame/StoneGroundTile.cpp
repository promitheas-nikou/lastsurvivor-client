#include "StoneGroundTile.h"
#include "ResourceLoader.h"

std::string StoneGroundTile::NAME;
ALLEGRO_BITMAP* StoneGroundTile::TEXTURE;
int StoneGroundTile::MINING_RESISTANCE;
int StoneGroundTile::DROP;

int StoneGroundTile::GetID() const
{
	return ID;
}

StoneGroundTile::StoneGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void StoneGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = data[DATA_JSON_DROP_KEY];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
}

ALLEGRO_BITMAP* StoneGroundTile::GetTexture() const
{
	return TEXTURE;
}

Item* StoneGroundTile::GetMiningResult(Tool* tool) const
{
	return MakeItem(DROP);
}

int StoneGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

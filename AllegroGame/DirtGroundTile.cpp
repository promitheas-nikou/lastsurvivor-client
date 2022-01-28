#include "DirtGroundTile.h"
#include "ResourceLoader.h"

std::string DirtGroundTile::NAME;
ALLEGRO_BITMAP* DirtGroundTile::TEXTURE;
int DirtGroundTile::DROP;
int DirtGroundTile::MINING_RESISTANCE;

int DirtGroundTile::GetID() const
{
	return ID;
}

DirtGroundTile::DirtGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void DirtGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = data[DATA_JSON_DROP_KEY];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
}

ALLEGRO_BITMAP* DirtGroundTile::GetTexture() const
{
	return TEXTURE;
}

Item* DirtGroundTile::GetMiningResult(Tool* tool) const
{
	return MakeItem(DROP);
}

int DirtGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

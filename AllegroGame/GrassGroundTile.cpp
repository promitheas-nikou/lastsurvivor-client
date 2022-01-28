#include "GrassGroundTile.h"
#include "ResourceLoader.h"

std::string GrassGroundTile::NAME;
ALLEGRO_BITMAP* GrassGroundTile::TEXTURE;
int GrassGroundTile::DROP;
int GrassGroundTile::MINING_RESISTANCE;

int GrassGroundTile::GetID() const
{
	return ID;
}

GrassGroundTile::GrassGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void GrassGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = data[DATA_JSON_DROP_KEY];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
}

ALLEGRO_BITMAP* GrassGroundTile::GetTexture() const
{
	return TEXTURE;
}

Item* GrassGroundTile::GetMiningResult(Tool* tool) const
{
	return MakeItem(DROP);
}

int GrassGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

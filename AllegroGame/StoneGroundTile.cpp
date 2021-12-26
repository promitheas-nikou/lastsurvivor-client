#include "StoneGroundTile.h"
#include "ResourceLoader.h"

std::string StoneGroundTile::NAME;
ALLEGRO_BITMAP* StoneGroundTile::TEXTURE;

int StoneGroundTile::GetID() const
{
	return ID;
}

StoneGroundTile::StoneGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void StoneGroundTile::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}

ALLEGRO_BITMAP* StoneGroundTile::GetTexture() const
{
	return TEXTURE;
}

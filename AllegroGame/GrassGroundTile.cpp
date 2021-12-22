#include "GrassGroundTile.h"
#include "ResourceLoader.h"

std::string GrassGroundTile::NAME;
ALLEGRO_BITMAP* GrassGroundTile::TEXTURE;

int GrassGroundTile::GetID() const
{
	return ID;
}

GrassGroundTile::GrassGroundTile(int x, int y) : GroundTile(x, y, NAME)
{}

void GrassGroundTile::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}

ALLEGRO_BITMAP* GrassGroundTile::GetTexture() const
{
	return TEXTURE;
}

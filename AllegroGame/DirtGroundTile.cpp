#include "DirtGroundTile.h"
#include "ResourceLoader.h"

std::string DirtGroundTile::NAME;
ALLEGRO_BITMAP* DirtGroundTile::TEXTURE;

int DirtGroundTile::GetID() const
{
	return ID;
}

DirtGroundTile::DirtGroundTile(int x, int y) : GroundTile(x, y, NAME)
{}

void DirtGroundTile::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}

ALLEGRO_BITMAP* DirtGroundTile::GetTexture() const
{
	return TEXTURE;
}

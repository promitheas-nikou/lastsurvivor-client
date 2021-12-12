#include "StoneTile.h"
#include "ResourceLoader.h"

std::string StoneTile::NAME;
ALLEGRO_BITMAP* StoneTile::TEXTURE;

int StoneTile::GetID() const
{
	return ID;
}

StoneTile::StoneTile(int x, int y) : Tile(x, y, NAME)
{}

void StoneTile::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}

ALLEGRO_BITMAP* StoneTile::GetTexture() const
{
	return TEXTURE;
}

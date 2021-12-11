#include "GrassTile.h"
#include "ResourceLoader.h"

std::string GrassTile::NAME;
ALLEGRO_BITMAP* GrassTile::TEXTURE;

int GrassTile::GetID() const
{
	return ID;
}

GrassTile::GrassTile(int x, int y) : Tile(x, y, NAME)
{}

void GrassTile::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}

ALLEGRO_BITMAP* GrassTile::GetTexture() const
{
	return TEXTURE;
}

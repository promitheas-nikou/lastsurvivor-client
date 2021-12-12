#include "DirtTile.h"
#include "ResourceLoader.h"

std::string DirtTile::NAME;
ALLEGRO_BITMAP* DirtTile::TEXTURE;

int DirtTile::GetID() const
{
	return ID;
}

DirtTile::DirtTile(int x, int y) : Tile(x, y, NAME)
{}

void DirtTile::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}

ALLEGRO_BITMAP* DirtTile::GetTexture() const
{
	return TEXTURE;
}

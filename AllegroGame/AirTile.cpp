#include "AirTile.h"

void AirTile::Draw() const
{
	return;
}

int AirTile::GetID() const
{
	return ID;
}

bool AirTile::IsTransparent() const
{
	return true;
}

bool AirTile::IsEmpty() const
{
	return true;
}

AirTile::AirTile(World* w, int x, int y): Tile(w, x, y, "")
{}

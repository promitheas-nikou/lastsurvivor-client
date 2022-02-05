#include "AirTile.h"

const std::string AirTile::ID = "tiles.air";

void AirTile::Draw() const
{
	return;
}

std::string AirTile::GetID() const
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

AirTile::AirTile(World* w, int x, int y): Tile(w, x, y, ToolType::NONE, 10, "Air")
{}

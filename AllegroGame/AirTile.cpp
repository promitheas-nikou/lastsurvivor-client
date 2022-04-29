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

std::string AirTile::GetName() const
{
	return "Air";
}

ToolType AirTile::GetOptimalToolType() const
{
	return ToolType::NONE;
}

int AirTile::GetMiningResistance() const
{
	return 0;
}

Tile* AirTile::Clone(World* w, int x, int y) const
{
	return new AirTile(w, x, y);
}

bool AirTile::IsTransparent() const
{
	return true;
}

bool AirTile::IsEmpty() const
{
	return true;
}

AirTile::AirTile(World* w, int x, int y): Tile(w, x, y)
{}

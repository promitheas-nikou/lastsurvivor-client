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

Tool::ToolType AirTile::GetOptimalToolType() const
{
	return Tool::ToolType::NONE;
}

float AirTile::GetMiningResistance() const
{
	return 0;
}

Tile* AirTile::Clone(World* w, int x, int y, Direction d) const
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

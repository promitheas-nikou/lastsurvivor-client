#include "Tile.h"
#include "AirTile.h"
#include "TreeTile.h"
#include "BerryBushTile.h"

Tile::Tile(World* w, int x, int y, ToolType t, int m, std::string n) : world(w), xpos(x), ypos(y), optimalToolType(t), miningResistance(m), name(n)
{}

Tile::Tile(World* w, int x, int y): world(w), xpos(x), ypos(y)
{}

void Tile::LoadAdditionalDataFromFile(std::ifstream &file)
{
	return;
}

void Tile::WriteAdditionalDataToFile(std::ofstream& file)
{
	return;
}

std::string Tile::GetName() const
{
	return name;
}

void Tile::TickUpdate()
{
	return;
}

void Tile::RandomTickUpdate()
{
	return;
}

void Tile::TileUpdate()
{
	return;
}

bool Tile::CanWalkThrough() const
{
	return this->IsEmpty();
}

bool Tile::canSwimThrough() const
{
	return false;
}

bool Tile::canFlyThrough() const
{
	return true;
}

bool Tile::IsTransparent() const
{
	return false;
}

bool Tile::IsEmpty() const
{
	return false;
}

void Tile::Use(PlayerEntity* user)
{}

bool Tile::MineWithTool(Tool* tool)
{
	if ((tool!=nullptr)&&(static_cast<char>(tool->GetMiningType()) & static_cast<char>(optimalToolType)))
		miningDamageDone += tool->GetMiningDamage();
	else
		miningDamageDone++;
	return miningDamageDone >= miningResistance;
}

const ItemBundle* Tile::GetMiningResult(Tool* tool) const
{
	return nullptr;
}

int Tile::GetMiningResistance() const
{
	return miningResistance;
}

int Tile::GetMiningDamageDone() const
{
	return miningDamageDone;
}

ToolType Tile::GetOptimalToolType() const
{
	return optimalToolType;
}

int Tile::GetXpos() const
{
	return xpos;
}

int Tile::GetYpos() const
{
	return ypos;
}

Tile* MakeTile(World* world, std::string id, int x, int y)
{
	if (id == AirTile::ID)
		return new AirTile(world, x, y);
	if (id == TreeTile::ID)
		return new TreeTile(world, x, y);
	if (id == BerryBushTile::ID)
		return new BerryBushTile(world, x, y);
	return nullptr;
}

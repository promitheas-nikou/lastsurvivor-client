#include "Tile.h"
#include "AirTile.h"
#include "TreeTile.h"
#include "BerryBushTile.h"
#include "FenceTile.h"

Tile::Tile(World* w, int x, int y): world(w), xpos(x), ypos(y)
{}

Item* Tile::PushItem(Item * i, Direction d, ItemIOInterface * from)
{
	return i;
}

Item* Tile::PullItem(Direction d, ItemIOInterface* to)
{
	return nullptr;
}

void Tile::LoadAdditionalDataFromFile(std::ifstream &file)
{
	return;
}

void Tile::WriteAdditionalDataToFile(std::ofstream& file)
{
	return;
}

bool Tile::DoesTickUpdates() const
{
	return false;
}

void Tile::TickUpdate(uint64_t T)
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

void Tile::DrawOver() const
{}

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

Direction Tile::GetDirection() const
{
	return Direction::GetDefaultDirection();
}

void Tile::InitForWorld(World* w)
{
	return;
}

void Tile::Use(PlayerEntity* user)
{}

bool Tile::MineWithTool(Tool* tool)
{
	if ((tool!=nullptr)&&(static_cast<char>(tool->GetToolType()) & static_cast<char>(this->GetOptimalToolType())))
		miningDamageDone += tool->GetMiningDamage();
	else
		miningDamageDone++;
	return miningDamageDone >= this->GetMiningResistance();
}

const ItemBundle* Tile::GetMiningResult(Tool* tool) const
{
	return nullptr;
}

float Tile::GetMiningDamageDone() const
{
	return miningDamageDone;
}

int Tile::GetXpos() const
{
	return xpos;
}

int Tile::GetYpos() const
{
	return ypos;
}

void Tile::RegisterLights()
{}

std::unordered_map<std::string, const Tile*> prototype_tiles;

Tile* MakeTile(World* world, std::string id, int x, int y, Direction d)
{
	const Tile* t = prototype_tiles[id];
	if (t == nullptr)
		return nullptr;
	return t->Clone(world, x, y, d);
}

void InitAllTilesForWorld(World* w)
{
	for (const std::pair<std::string, const Tile*>& tile : prototype_tiles)
		const_cast<Tile*>(tile.second)->InitForWorld(w);
}

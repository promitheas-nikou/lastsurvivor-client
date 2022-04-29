#include "GroundTile.h"
#include "GrassGroundTile.h"
#include "StoneGroundTile.h"
#include "DirtGroundTile.h"
#include "SandGroundTile.h"
#include "WaterGroundTile.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#include <format>
#include "ResourceLoader.h"

GroundTile::GroundTile(World* w, int x, int y, std::string n, ToolType t) : world{ w }, xpos{ x }, ypos{ y }, name{ n }, requiredTool{ t } {}

void GroundTile::LoadAdditionalDataFromFile(std::ifstream &file)
{
    return;
}

void GroundTile::WriteAdditionalDataToFile(std::ofstream& file)
{
    return;
}

std::string GroundTile::GetName() const
{
    return name;
}

int GroundTile::GetXpos() const
{
    return xpos;
}

int GroundTile::GetYpos() const
{
    return ypos;
}

void GroundTile::TickUpdate()
{
    return;
}

void GroundTile::TileUpdate()
{
    return;
}

int GroundTile::GetMiningResistance() const
{
    return 10;
}

ToolType GroundTile::GetRequiredToolType() const
{
    return requiredTool;
}

int GroundTile::GetDamageDealtByTool(Tool* tool) const
{
    if (tool == nullptr)
        return 1;
    return (static_cast<char>(tool->GetMiningType()) & static_cast<char>(GetRequiredToolType())) ? tool->GetMiningDamage() : 1;
}

void GroundTile::Use(PlayerEntity* p)
{}

const ItemBundle* GroundTile::GetMiningResult(Tool* tool) const
{
    return nullptr;
}

float GroundTile::GetFrictionModifier() const
{
    return 1.0f;
}

void GroundTile::PlaySound(SoundType t) const
{}

std::unordered_map<std::string, const GroundTile*> prototype_gtiles;

GroundTile* MakeGroundTile(World* world, std::string id, int x, int y)
{
    const GroundTile* gt = prototype_gtiles[id];
    if (gt == nullptr)
        return nullptr;
    return gt->Clone(world, x, y);
}

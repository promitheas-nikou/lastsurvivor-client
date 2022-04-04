#include "GroundTile.h"
#include "GrassGroundTile.h"
#include "StoneGroundTile.h"
#include "DirtGroundTile.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#include <format>
#include "ResourceLoader.h"

GroundTile::GroundTile(World* w, int x, int y, std::string n) : world{ w }, xpos{ x }, ypos{ y }, name{ n }, requiredTool{ ToolType::PICKAXE } {}


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
    return 3;  
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

const ItemBundle* GroundTile::GetMiningResult(Tool* tool) const
{
    return nullptr;
}

GroundTile* MakeGroundTile(World* world, std::string id, int x, int y)
{
    if (id == GrassGroundTile::ID)
        return new GrassGroundTile(world, x, y);
    else if (id == DirtGroundTile::ID)
        return new DirtGroundTile(world, x, y);
    else if (id == StoneGroundTile::ID)
        return new StoneGroundTile(world, x, y);
    return nullptr;
}

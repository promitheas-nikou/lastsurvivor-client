#include "GroundTile.h"
#include "GrassGroundTile.h"
#include "StoneGroundTile.h"
#include "DirtGroundTile.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#include <format>
#include "ResourceLoader.h"

GroundTile::GroundTile(World* w, int x, int y, std::string n) : world{ w }, xpos{ x }, ypos{ y }, name{ n }, requiredTool{ ToolType::PICKAXE } {}

ALLEGRO_BITMAP* GroundTile::GetTexture() const
{
    return nullptr;
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

void GroundTile::Draw() const
{
    al_draw_bitmap(GetTexture(), xpos*128, ypos*128, 0);
    //al_draw_textf(loaded_font, al_map_rgb(255, 255, 255), xpos * 128, ypos * 128, 0, "%d:%d", xpos, ypos);
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

Item* GroundTile::GetMiningResult(Tool* tool) const
{
    return nullptr;
}

GroundTile* MakeGroundTile(World* world, int id, int x, int y)
{
    switch (id)
    {
    case GrassGroundTile::ID:
        return new GrassGroundTile(world, x, y);
    case DirtGroundTile::ID:
        return new DirtGroundTile(world, x, y);
    case StoneGroundTile::ID:
        return new StoneGroundTile(world, x, y);
    }
}

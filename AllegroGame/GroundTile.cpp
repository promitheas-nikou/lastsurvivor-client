#include "GroundTile.h"
#include "GrassGroundTile.h"
#include "StoneGroundTile.h"
#include "DirtGroundTile.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#include <format>
#include "ResourceLoader.h"

GroundTile::GroundTile(int x, int y, std::string n): xpos(x), ypos(y), name(n) {}

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
    //al_draw_text(loaded_font, al_map_rgb(255, 255, 255), xpos * 128, ypos * 128, 0, std::format("{}:{}", xpos, ypos).c_str());
}

int GroundTile::GetMiningResistance() const
{
    return 0;
}

GroundTile* MakeGroundTile(int id, int x, int y)
{
    switch (id)
    {
    case GrassGroundTile::ID:
        return new GrassGroundTile(x, y);
    case DirtGroundTile::ID:
        return new DirtGroundTile(x, y);
    case StoneGroundTile::ID:
        return new StoneGroundTile(x, y);
    }
}

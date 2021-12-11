#include "Tile.h"
#include "GrassTile.h"
#include "allegro5/allegro_font.h"
#include <iostream>
#include <format>
#include "ResourceLoader.h"

Tile::Tile(int x, int y, std::string n): xpos(x), ypos(y), name(n) {}

ALLEGRO_BITMAP* Tile::GetTexture() const
{
    return nullptr;
}

std::string Tile::GetName() const
{
    return name;
}

int Tile::GetXpos() const
{
    return xpos;
}

int Tile::GetYpos() const
{
    return ypos;
}

void Tile::TickUpdate()
{
    return;
}

void Tile::TileUpdate()
{
    return;
}

void Tile::Draw() const
{
    al_draw_bitmap(GetTexture(), xpos*128, ypos*128, 0);
}

int Tile::GetMiningResistance() const
{
    return 0;
}

Tile* MakeTile(int id, int x, int y)
{
    switch (id)
    {
    case GrassTile::ID:
        return new GrassTile(x, y);
    }
}

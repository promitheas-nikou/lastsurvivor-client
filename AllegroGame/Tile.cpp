#include "Tile.h"
#include "AirTile.h"

Tile::Tile(World* w, int x, int y, std::string n) : world(w), xpos(x), ypos(y), name(n)
{}

ALLEGRO_BITMAP* Tile::GetTexture() const
{
	return nullptr;
}

std::string Tile::GetName() const
{
	return name;
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
	al_draw_bitmap(GetTexture(), xpos * 128, ypos * 128, 0);
	//al_draw_text(loaded_font, al_map_rgb(255, 255, 255), xpos * 128, ypos * 128, 0, std::format("{}:{}", xpos, ypos).c_str());
}

bool Tile::IsTransparent() const
{
	return false;
}

bool Tile::IsEmpty() const
{
	return false;
}

int Tile::GetMiningResistance() const
{
	return 1;
}

int Tile::GetXpos() const
{
	return xpos;
}

int Tile::GetYpos() const
{
	return ypos;
}

Tile* MakeTile(World* world, int id, int x, int y)
{
	return new AirTile(world, x, y);
}

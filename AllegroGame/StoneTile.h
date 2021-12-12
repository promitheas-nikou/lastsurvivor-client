#pragma once
#include "Tile.h"
class StoneTile:
	public Tile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const int ID = 3;

	int GetID() const final;

	StoneTile(int x, int y);

	static void Init(nlohmann::json data);
	ALLEGRO_BITMAP* GetTexture() const final;
};


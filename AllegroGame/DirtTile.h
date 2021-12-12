#pragma once
#include "Tile.h"
class DirtTile :
    public Tile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const int ID = 2;

	int GetID() const final;

	DirtTile(int x, int y);

	static void Init(nlohmann::json data);
	ALLEGRO_BITMAP* GetTexture() const final;

};


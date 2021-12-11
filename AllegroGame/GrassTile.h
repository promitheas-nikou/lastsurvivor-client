#pragma once
#include "Tile.h"
#include "json.h"

class GrassTile:
	public Tile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const int ID = 1;

	int GetID() const final;

	GrassTile(int x, int y);
	
	static void Init(nlohmann::json data);
	ALLEGRO_BITMAP* GetTexture() const final;
	
};


#pragma once
#include "GroundTile.h"
#include "json.h"

class GrassGroundTile:
	public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const int ID = 1;

	int GetID() const final;

	GrassGroundTile(World* w, int x, int y);
	
	static void Init(nlohmann::json data);
	ALLEGRO_BITMAP* GetTexture() const final;
	
};


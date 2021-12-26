#pragma once
#include "GroundTile.h"
class DirtGroundTile :
    public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const int ID = 2;

	int GetID() const final;

	DirtGroundTile(World* w, int x, int y);

	static void Init(nlohmann::json data);
	ALLEGRO_BITMAP* GetTexture() const final;

};


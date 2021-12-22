#pragma once
#include "GroundTile.h"
class StoneGroundTile:
	public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const int ID = 3;

	int GetID() const final;

	StoneGroundTile(int x, int y);

	static void Init(nlohmann::json data);
	ALLEGRO_BITMAP* GetTexture() const final;
};


#pragma once
#include "GroundTile.h"
class StoneGroundTile:
	public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
	static int DROP;
	static int MINING_RESISTANCE;
public:
	static const int ID = 3;

	int GetID() const final;

	StoneGroundTile(World* w, int x, int y);

	static void Init(nlohmann::json data);

	ALLEGRO_BITMAP* GetTexture() const final;

	Item* GetMiningResult(Tool* tool) const final;

	int GetMiningResistance() const final;

	virtual ~StoneGroundTile() = default;
};


#pragma once

#include "PlaceableItem.h"

class WheatSeedsItem :
	public PlaceableItem
{
private:
	static std::string NAME;
	static std::string DESCRIPTION;
	static std::string TILE_ID;
	static ALLEGRO_BITMAP* TEXTURE;

public:

	static const std::string ID;

	std::string GetID() const final;

	WheatSeedsItem();

	virtual Tile* GetTile(World* w, int xpos, int ypos, Direction d) override;

	virtual Item* Clone() const override;

	void Draw(int x, int y, int width, int height) const final;

	static void Init(nlohmann::json data);

	virtual ~WheatSeedsItem() = default;

};


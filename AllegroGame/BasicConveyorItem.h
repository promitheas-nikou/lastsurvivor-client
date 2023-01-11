#pragma once

#include "PlaceableItem.h"

class BasicConveyorItem :
	public PlaceableItem
{
private:
	static std::string NAME;
	static std::string TILE_ID;
	static std::string DESCRIPTION;
	static ALLEGRO_BITMAP* TEXTURE;

public:

	static const std::string ID;

	std::string GetID() const final;

    virtual Tile* GetTile(World* w, int x, int y, Direction d) final;

	BasicConveyorItem();

	virtual Item* Clone() const final;

	void Draw(int x, int y, int width, int height) const final;

	static void Init(nlohmann::json data);

	virtual ~BasicConveyorItem() = default;

};


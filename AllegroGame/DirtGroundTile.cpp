#include "DirtGroundTile.h"
#include "ResourceLoader.h"

std::string DirtGroundTile::NAME;
ALLEGRO_BITMAP* DirtGroundTile::TEXTURE;
int DirtGroundTile::DROP;
int DirtGroundTile::MINING_RESISTANCE;
const std::string DirtGroundTile::ID = "gtiles.dirt";


std::string DirtGroundTile::GetID() const
{
	return ID;
}

DirtGroundTile::DirtGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME)
{}

void DirtGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = data[DATA_JSON_DROP_KEY];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
}

void DirtGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

Item* DirtGroundTile::GetMiningResult(Tool* tool) const
{
	//return MakeItem(DROP);
	return nullptr;
}

int DirtGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

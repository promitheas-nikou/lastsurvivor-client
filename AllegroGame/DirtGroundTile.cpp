#include "DirtGroundTile.h"
#include "ResourceLoader.h"

std::string DirtGroundTile::NAME;
ALLEGRO_BITMAP* DirtGroundTile::TEXTURES[2];
const LootBundle* DirtGroundTile::DROP;
int DirtGroundTile::MINING_RESISTANCE;
ToolType DirtGroundTile::TOOL_TYPE;
const std::string DirtGroundTile::ID = "gtiles.dirt";
AudioMultiTrackCollection DirtGroundTile::AUDIO_TRACKS;


std::string DirtGroundTile::GetID() const
{
	return ID;
}

GroundTile* DirtGroundTile::Clone(World* w, int x, int y) const
{
	return new DirtGroundTile(w, x, y);
}

DirtGroundTile::DirtGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void DirtGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];

	for (int i = 0; i < 2; i++)
		TEXTURES[i] = game_GetTexture(data[DATA_JSON_TEXTURE_LIST_KEY][i]);
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

void DirtGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURES[0], xpos * 128, ypos * 128, 0);
}

void DirtGroundTile::Till()
{
	isTilled = !isTilled;
}

bool DirtGroundTile::IsTillable() const
{
	return true;
}

bool DirtGroundTile::DoesSupportPlants() const
{
	return isTilled;
}

const ItemBundle* DirtGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

void DirtGroundTile::PlaySound(SoundType t) const
{
	AUDIO_TRACKS.Play(t);
}

int DirtGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

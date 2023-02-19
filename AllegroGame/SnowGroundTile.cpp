#include "SnowGroundTile.h"
#include "ResourceLoader.h"
#include "Tool.h"

std::string SnowGroundTile::NAME;
ALLEGRO_BITMAP* SnowGroundTile::TEXTURE;
const LootBundle* SnowGroundTile::DROP;
int SnowGroundTile::MINING_RESISTANCE;
ToolType SnowGroundTile::TOOL_TYPE;
const std::string SnowGroundTile::ID = "gtiles.snow";
AudioMultiTrackCollection SnowGroundTile::AUDIO_TRACKS;

std::string SnowGroundTile::GetID() const
{
	return ID;
}

SnowGroundTile::SnowGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void SnowGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

void SnowGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* SnowGroundTile::Clone(World* w, int x, int y) const
{
	return new SnowGroundTile(w, x, y);
}

const ItemBundle* SnowGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

int SnowGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

void SnowGroundTile::PlaySound(SoundType t) const
{
	AUDIO_TRACKS.Play(t);
}

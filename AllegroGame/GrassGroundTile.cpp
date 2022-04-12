#include "GrassGroundTile.h"
#include "ResourceLoader.h"
#include "Tool.h"

std::string GrassGroundTile::NAME;
ALLEGRO_BITMAP* GrassGroundTile::TEXTURE;
const ItemBundle* GrassGroundTile::DROP;
int GrassGroundTile::MINING_RESISTANCE;
ToolType GrassGroundTile::TOOL_TYPE;
const std::string GrassGroundTile::ID = "gtiles.grass";
AudioMultiTrackCollection GrassGroundTile::AUDIO_TRACKS;

std::string GrassGroundTile::GetID() const
{
	return ID;
}

GrassGroundTile::GrassGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void GrassGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

void GrassGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

const ItemBundle* GrassGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP;
}

int GrassGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

void GrassGroundTile::PlaySound(SoundType t) const
{
	AUDIO_TRACKS.Play(t);
}

#include "IceGroundTile.h"
#include "ResourceLoader.h"
#include "Tool.h"

std::string IceGroundTile::NAME;
ALLEGRO_BITMAP* IceGroundTile::TEXTURE;
const LootBundle* IceGroundTile::DROP;
int IceGroundTile::MINING_RESISTANCE;
ToolType IceGroundTile::TOOL_TYPE;
const std::string IceGroundTile::ID = "gtiles.ice";
AudioMultiTrackCollection IceGroundTile::AUDIO_TRACKS;

std::string IceGroundTile::GetID() const
{
	return ID;
}

IceGroundTile::IceGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void IceGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

void IceGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* IceGroundTile::Clone(World* w, int x, int y) const
{
	return new IceGroundTile(w, x, y);
}

const ItemBundle* IceGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

float IceGroundTile::GetFrictionModifier() const
{
	return .2f;
}

int IceGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

void IceGroundTile::PlaySound(SoundType t) const
{
	AUDIO_TRACKS.Play(t);
}

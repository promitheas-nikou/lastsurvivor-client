#include "WaterGroundTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"

std::string WaterGroundTile::NAME;
ALLEGRO_BITMAP* WaterGroundTile::TEXTURE;
const LootBundle* WaterGroundTile::DROP;
int WaterGroundTile::MINING_RESISTANCE;
ToolType WaterGroundTile::TOOL_TYPE;
const std::string WaterGroundTile::ID = "gtiles.water";

std::string WaterGroundTile::GetID() const
{
	return ID;
}

WaterGroundTile::WaterGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void WaterGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void WaterGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* WaterGroundTile::Clone(World* w, int x, int y) const
{
	return new WaterGroundTile(w, x, y);
}

void WaterGroundTile::Use(PlayerEntity* p)
{
	p->water = std::min(p->MAX_WATER, p->water+5);
}

const ItemBundle* WaterGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

int WaterGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

float WaterGroundTile::GetFrictionModifier() const
{
    return .70f;
}

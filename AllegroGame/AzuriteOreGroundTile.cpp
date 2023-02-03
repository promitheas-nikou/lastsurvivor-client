#include "AzuriteOreGroundTile.h"
#include "ResourceLoader.h"

std::string AzuriteOreGroundTile::NAME;
ALLEGRO_BITMAP* AzuriteOreGroundTile::TEXTURE;
int AzuriteOreGroundTile::MINING_RESISTANCE;
const LootBundle* AzuriteOreGroundTile::DROP;
ToolType AzuriteOreGroundTile::TOOL_TYPE;

const std::string AzuriteOreGroundTile::ID = "gtiles.azurite_ore";

std::string AzuriteOreGroundTile::GetID() const
{
	return ID;
}

AzuriteOreGroundTile::AzuriteOreGroundTile(World* w, int x, int y) : GroundTile(w, x, y, NAME, TOOL_TYPE)
{}

void AzuriteOreGroundTile::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
}

void AzuriteOreGroundTile::Draw() const
{
	al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

GroundTile* AzuriteOreGroundTile::Clone(World* w, int x, int y) const
{
	return new AzuriteOreGroundTile(w, x, y);
}

const ItemBundle* AzuriteOreGroundTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

int AzuriteOreGroundTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

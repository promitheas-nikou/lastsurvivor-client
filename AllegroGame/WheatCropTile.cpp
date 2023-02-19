#include "WheatCropTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "World.h"

int WheatCropTile::MINING_RESISTANCE;
ToolType WheatCropTile::TOOL_TYPE;
std::string WheatCropTile::NAME;
ALLEGRO_BITMAP* WheatCropTile::TEXTURE;
const std::string WheatCropTile::ID = "tiles.wheat_crop";
const LootBundle* WheatCropTile::DROP;

std::string WheatCropTile::GetID() const
{
    return ID;
}

bool WheatCropTile::IsTransparent() const
{
    return false;
}

bool WheatCropTile::CanWalkThrough() const
{
    return false;
}

ToolType WheatCropTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float WheatCropTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string WheatCropTile::GetName() const
{
    return NAME;
}

Tile* WheatCropTile::Clone(World* w, int x, int y, Direction d) const
{
    return new WheatCropTile(w, x, y);
}

const ItemBundle* WheatCropTile::GetMiningResult(Tool* tool) const
{
    return WheatCropTile::DROP->ConstCollapseToItemBundle();
}

void WheatCropTile::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void WheatCropTile::Init(nlohmann::json data)
{
    TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
}


WheatCropTile::WheatCropTile(World* w, int x, int y): Tile(w, x, y)
{

}

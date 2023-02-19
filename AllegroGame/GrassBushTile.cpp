#include "GrassBushTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "World.h"

float GrassBushTile::MINING_RESISTANCE;
ToolType GrassBushTile::TOOL_TYPE;
std::string GrassBushTile::NAME;
ALLEGRO_BITMAP* GrassBushTile::TEXTURE;
const std::string GrassBushTile::ID = "tiles.grass_bush";
const LootBundle* GrassBushTile::DROP;

std::string GrassBushTile::GetID() const
{
    return ID;
}

bool GrassBushTile::IsTransparent() const
{
    return false;
}

bool GrassBushTile::CanWalkThrough() const
{
    return false;
}

ToolType GrassBushTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float GrassBushTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string GrassBushTile::GetName() const
{
    return NAME;
}

Tile* GrassBushTile::Clone(World* w, int x, int y, Direction d) const
{
    return new GrassBushTile(w, x, y);
}

const ItemBundle* GrassBushTile::GetMiningResult(Tool* tool) const
{
    return GrassBushTile::DROP->ConstCollapseToItemBundle();
}

void GrassBushTile::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void GrassBushTile::Init(nlohmann::json data)
{
    TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
}


GrassBushTile::GrassBushTile(World* w, int x, int y): Tile(w, x, y)
{

}

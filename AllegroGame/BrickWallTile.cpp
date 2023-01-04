#include "BrickWallTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "World.h"

int BrickWallTile::MINING_RESISTANCE;
ToolType BrickWallTile::TOOL_TYPE;
std::string BrickWallTile::NAME;
ALLEGRO_BITMAP* BrickWallTile::TEXTURE;
const std::string BrickWallTile::ID = "tiles.brick_wall";
const LootBundle* BrickWallTile::DROP;

std::string BrickWallTile::GetID() const
{
    return ID;
}

bool BrickWallTile::IsTransparent() const
{
    return false;
}

bool BrickWallTile::CanWalkThrough() const
{
    return false;
}

Tool::ToolType BrickWallTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float BrickWallTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string BrickWallTile::GetName() const
{
    return NAME;
}

Tile* BrickWallTile::Clone(World* w, int x, int y, Direction d) const
{
    return new BrickWallTile(w, x, y);
}

const ItemBundle* BrickWallTile::GetMiningResult(Tool* tool) const
{
    return BrickWallTile::DROP->ConstCollapseToItemBundle();
}

void BrickWallTile::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void BrickWallTile::Init(nlohmann::json data)
{
    TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];  
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
}


BrickWallTile::BrickWallTile(World* w, int x, int y): Tile(w, x, y)
{

}

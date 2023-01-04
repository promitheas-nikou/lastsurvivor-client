#include "StoneBrickWallTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "World.h"

int StoneBrickWallTile::MINING_RESISTANCE;
ToolType StoneBrickWallTile::TOOL_TYPE;
std::string StoneBrickWallTile::NAME;
ALLEGRO_BITMAP* StoneBrickWallTile::TEXTURE;
const std::string StoneBrickWallTile::ID = "tiles.stone_brick_wall";
const LootBundle* StoneBrickWallTile::DROP;

std::string StoneBrickWallTile::GetID() const
{
    return ID;
}

bool StoneBrickWallTile::IsTransparent() const
{
    return false;
}

bool StoneBrickWallTile::CanWalkThrough() const
{
    return false;
}

Tool::ToolType StoneBrickWallTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float StoneBrickWallTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string StoneBrickWallTile::GetName() const
{
    return NAME;
}

Tile* StoneBrickWallTile::Clone(World* w, int x, int y, Direction d) const
{
    return new StoneBrickWallTile(w, x, y);
}

const ItemBundle* StoneBrickWallTile::GetMiningResult(Tool* tool) const
{
    return StoneBrickWallTile::DROP->ConstCollapseToItemBundle();
}

void StoneBrickWallTile::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void StoneBrickWallTile::Init(nlohmann::json data)
{
    TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
}


StoneBrickWallTile::StoneBrickWallTile(World* w, int x, int y): Tile(w, x, y)
{

}

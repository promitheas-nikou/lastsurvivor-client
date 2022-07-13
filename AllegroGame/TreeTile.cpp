#include "TreeTile.h"
#include "ResourceLoader.h"

int TreeTile::MINING_RESISTANCE;
ToolType TreeTile::TOOL_TYPE;
std::string TreeTile::NAME;
ALLEGRO_BITMAP* TreeTile::TEXTURES[4];
const std::string TreeTile::ID = "tiles.tree";
const LootBundle* TreeTile::DROP;

std::string TreeTile::GetID() const
{
    return ID;
}

bool TreeTile::IsTransparent() const
{
    return false;
}

bool TreeTile::CanWalkThrough() const
{
    return false;
}

ToolType TreeTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

int TreeTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string TreeTile::GetName() const
{
    return NAME;
}

Tile* TreeTile::Clone(World* w, int x, int y) const
{
    return new TreeTile(w, x, y);
}

void TreeTile::RandomTickUpdate()
{
    growthTimer = std::min(600, growthTimer+20);
}

const ItemBundle* TreeTile::GetMiningResult(Tool* tool) const
{
    return TreeTile::DROP->ConstCollapseToItemBundle();
}

void TreeTile::Draw() const
{
    al_draw_bitmap(TEXTURES[TreeTile::growthTimer/200], xpos * 128, ypos * 128, 0);
}

void TreeTile::Init(nlohmann::json data)
{
    for (int i = 0; i < 4; i++)
        TEXTURES[i] = loaded_bitmaps[data[DATA_JSON_TEXTURE_LIST_KEY][i]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
}

TreeTile::TreeTile(World* w, int x, int y): Tile(w, x, y), growthTimer{600}
{

}

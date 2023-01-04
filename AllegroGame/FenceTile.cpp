#include "FenceTile.h"
#include "ResourceLoader.h"

ALLEGRO_BITMAP* FenceTile::TEXTURES[16];
ToolType FenceTile::TOOL_TYPE;
int FenceTile::MINING_RESISTANCE;
const LootBundle* FenceTile::DROP;
std::string FenceTile::NAME;

const std::string FenceTile::ID = "tiles.fence";

std::string FenceTile::GetID() const
{
    return ID;
}

bool FenceTile::IsTransparent() const
{
    return true;
}

bool FenceTile::CanWalkThrough() const
{
    return false;
}

Tool::ToolType FenceTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float FenceTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string FenceTile::GetName() const
{
    return NAME;
}

const ItemBundle* FenceTile::GetMiningResult(Tool* tool) const
{
    return DROP->ConstCollapseToItemBundle();
}

bool FenceTile::ShouldConnect(Tile* t) const
{
    return dynamic_cast<FenceTile*>(t)!=nullptr;
}

void FenceTile::Draw() const
{
    al_draw_bitmap(TEXTURES[GetConnectionsChar()], xpos * 128, ypos * 128, 0);
}

Tile* FenceTile::Clone(World* w, int x, int y, Direction d) const
{
    return new FenceTile(w, x, y);
}

void FenceTile::Init(nlohmann::json data)
{
    for (int i = 0; i < 16; i++)
        TEXTURES[i] = loaded_bitmaps[data[DATA_JSON_TEXTURE_LIST_KEY][i]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
}

FenceTile::FenceTile(World* w, int x, int y, char connections) : ConnectingTile(w, x, y, connections)
{}

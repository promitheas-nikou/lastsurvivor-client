#include "BerryBushTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"

int BerryBushTile::MINING_RESISTANCE;
ToolType BerryBushTile::TOOL_TYPE;
std::string BerryBushTile::NAME;
ALLEGRO_BITMAP* BerryBushTile::TEXTURES[2];
const std::string BerryBushTile::ID = "tiles.berry_bush";
const ItemBundle* BerryBushTile::DROP;

std::string BerryBushTile::GetID() const
{
    return ID;
}

bool BerryBushTile::IsTransparent() const
{
    return false;
}

bool BerryBushTile::CanWalkThrough() const
{
    return false;
}

void BerryBushTile::RandomTickUpdate()
{
    growthTimer = std::min(600, growthTimer+100);
}

const ItemBundle* BerryBushTile::GetMiningResult(Tool* tool) const
{
    return BerryBushTile::DROP;
}

void BerryBushTile::Draw() const
{
    al_draw_bitmap(TEXTURES[BerryBushTile::growthTimer/600], xpos * 128, ypos * 128, 0);
}

const ItemBundle* COLLECT;

void BerryBushTile::Use(PlayerEntity* p)
{
    if (growthTimer == 600)
    {
        growthTimer = 0;
        p->GiveConstItemBundle(COLLECT);
    }
}

void BerryBushTile::Init(nlohmann::json data)
{
    for (int i = 0; i < 2; i++)
        TEXTURES[i] = loaded_bitmaps[data[DATA_JSON_TEXTURE_LIST_KEY][i]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
    COLLECT = loaded_loot_bundles[data[DATA_JSON_COLLECT_KEY]];
}

BerryBushTile::BerryBushTile(World* w, int x, int y): Tile(w, x, y, TOOL_TYPE, MINING_RESISTANCE, NAME), growthTimer{0}
{

}

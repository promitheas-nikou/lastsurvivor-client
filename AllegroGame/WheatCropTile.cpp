#include "WheatCropTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "World.h"

int WheatCropTile::MINING_RESISTANCE;
ToolType WheatCropTile::TOOL_TYPE;
std::string WheatCropTile::NAME;
ALLEGRO_BITMAP* WheatCropTile::TEXTURES[5];
const std::string WheatCropTile::ID = "tiles.wheat_crop";
const LootBundle* WheatCropTile::DROPS[2];

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
    return true;
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

void WheatCropTile::RandomTickUpdate()
{
    age = std::min(age + 1, TICKS_UNTIL_GROWN);
}

Tile* WheatCropTile::Clone(World* w, int x, int y, Direction d) const
{
    return new WheatCropTile(w, x, y);
}

const ItemBundle* WheatCropTile::GetMiningResult(Tool* tool) const
{
    return WheatCropTile::DROPS[((age/TICKS_PER_STAGE)==MAX_GROWTH_STAGES-1)?1:0]->ConstCollapseToItemBundle();
}

void WheatCropTile::Draw() const
{
    al_draw_bitmap(TEXTURES[age/TICKS_PER_STAGE], xpos * 128, ypos * 128, 0);
}

void WheatCropTile::Init(nlohmann::json data)
{
    for (int i = 0; i < MAX_GROWTH_STAGES; i++)
        TEXTURES[i] = game_GetTexture(data[DATA_JSON_TEXTURE_LIST_KEY][i]);
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    for(int i=0;i<2;i++)
        DROPS[i] = game_GetLootBundle(data[DATA_JSON_DROP_KEY][i]);
}


WheatCropTile::WheatCropTile(World* w, int x, int y) : Tile(w, x, y), age{ 0 }
{

}

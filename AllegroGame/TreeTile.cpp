#include "TreeTile.h"
#include "ResourceLoader.h"

int TreeTile::MINING_RESISTANCE;
ToolType TreeTile::TOOL_TYPE;
std::string TreeTile::NAME;
ALLEGRO_BITMAP* TreeTile::TEXTURES[4];


int TreeTile::GetID() const
{
    return ID;
}

bool TreeTile::IsTransparent() const
{
    return true;
}

ALLEGRO_BITMAP* TreeTile::GetTexture() const
{
    return TEXTURES[growthTimer/150];
}

void TreeTile::RandomTickUpdate()
{
    growthTimer = std::min(600-1, growthTimer+20);
}

void TreeTile::Init(nlohmann::json data)
{
    for (int i = 0; i < 4; i++)
        TEXTURES[i] = loaded_bitmaps[data[DATA_JSON_TEXTURE_LIST_KEY][i]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString((std::string)data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
}

TreeTile::TreeTile(World* w, int x, int y): Tile(w, x, y, TOOL_TYPE, MINING_RESISTANCE, NAME), growthTimer{0}
{

}

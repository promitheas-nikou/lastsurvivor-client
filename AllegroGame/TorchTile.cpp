#include "TorchTile.h"
#include "ResourceLoader.h"
#include "World.h"

int TorchTile::MINING_RESISTANCE;
ToolType TorchTile::TOOL_TYPE;
std::string TorchTile::NAME;
ALLEGRO_BITMAP* TorchTile::TEXTURE;
const std::string TorchTile::ID = "tiles.torch";
const LootBundle* TorchTile::DROP;
float TorchTile::BRIGHTNESS;

std::string TorchTile::GetID() const
{
    return ID;
}

bool TorchTile::IsTransparent() const
{
    return false;
}

bool TorchTile::CanWalkThrough() const
{
    return false;
}

Tool::ToolType TorchTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float TorchTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string TorchTile::GetName() const
{
    return NAME;
}

void TorchTile::RegisterLights()
{
    world->RegisterLight(World::Light(GetXpos() + .5f, GetYpos() + .5f,BRIGHTNESS));
}

Tile* TorchTile::Clone(World* w, int x, int y, Direction d) const
{
    return new TorchTile(w, x, y);
}

const ItemBundle* TorchTile::GetMiningResult(Tool* tool) const
{
    return DROP->ConstCollapseToItemBundle();
}

void TorchTile::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void TorchTile::Init(nlohmann::json data)
{
    TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
    BRIGHTNESS = data[DATA_JSON_BRIGHTNESS_KEY];
}

TorchTile::TorchTile(World* w, int x, int y): Tile(w, x, y)
{

}

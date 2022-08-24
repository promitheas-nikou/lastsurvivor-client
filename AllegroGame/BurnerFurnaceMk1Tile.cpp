#include "BurnerFurnaceMk1Tile.h"
#include "ResourceLoader.h"

int BurnerFurnaceMk1Tile::MINING_RESISTANCE;
ToolType BurnerFurnaceMk1Tile::TOOL_TYPE;
std::string BurnerFurnaceMk1Tile::NAME;
GUI* BurnerFurnaceMk1Tile::TILE_GUI;
ALLEGRO_BITMAP* BurnerFurnaceMk1Tile::TEXTURES[2];
const std::string BurnerFurnaceMk1Tile::ID = "tiles.burner_furnace_mk1";
const LootBundle* BurnerFurnaceMk1Tile::DROP;
float BurnerFurnaceMk1Tile::BRIGHTNESS;

std::string BurnerFurnaceMk1Tile::GetID() const
{
    return ID;
}

bool BurnerFurnaceMk1Tile::IsTransparent() const
{
    return false;
}

bool BurnerFurnaceMk1Tile::CanWalkThrough() const
{
    return false;
}

void BurnerFurnaceMk1Tile::Use(PlayerEntity* user)
{
    user->DisplayTileGUI(this,TILE_GUI);
}

ToolType BurnerFurnaceMk1Tile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

int BurnerFurnaceMk1Tile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string BurnerFurnaceMk1Tile::GetName() const
{
    return NAME;
}

void BurnerFurnaceMk1Tile::RegisterLights()
{
    world->RegisterLight(World::Light(GetXpos() + .5f, GetYpos() + .5f, BRIGHTNESS));
}

Tile* BurnerFurnaceMk1Tile::Clone(World* w, int x, int y) const
{
    return new BurnerFurnaceMk1Tile(w, x, y);
}

const ItemBundle* BurnerFurnaceMk1Tile::GetMiningResult(Tool* tool) const
{
    return DROP->ConstCollapseToItemBundle();
}

void BurnerFurnaceMk1Tile::Draw() const
{
    al_draw_bitmap(TEXTURES[0], xpos * 128, ypos * 128, 0);
}

void BurnerFurnaceMk1Tile::Init(nlohmann::json data)
{
    for (int i = 0; i < 2; i++)
        TEXTURES[i] = loaded_bitmaps[data[DATA_JSON_TEXTURE_LIST_KEY][i]];
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = loaded_loot_bundles[data[DATA_JSON_DROP_KEY]];
    BRIGHTNESS = data[DATA_JSON_BRIGHTNESS_KEY];
    //TILE_GUI = new BurnerFurnaceMk1Tile::TileGUI();
}

BurnerFurnaceMk1Tile::BurnerFurnaceMk1Tile(World* w, int x, int y) : Tile(w, x, y)
{

}

void BurnerFurnaceMk1Tile::TileGUI::PreDrawThisGUI()
{
    al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(150, 150, 150, 150));
}


void BurnerFurnaceMk1Tile::TileGUI::PostDrawThisGUI()
{
}

BurnerFurnaceMk1Tile::TileGUI::TileGUI(PlayerEntity* p)
{
    
}

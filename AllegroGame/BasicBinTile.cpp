#include "BasicBinTile.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "SimpleItemInventory.h"
#include "SimpleInventoryGUI.h"
#include "World.h"

int BasicBinTile::MINING_RESISTANCE;
ToolType BasicBinTile::TOOL_TYPE;
std::string BasicBinTile::NAME;
ALLEGRO_BITMAP* BasicBinTile::TEXTURE;
BasicBinTile::TileGUI* BasicBinTile::TILE_GUI;
const std::string BasicBinTile::ID = "tiles.basic_bin";
const LootBundle* BasicBinTile::DROP;

std::string BasicBinTile::GetID() const
{
    return ID;
}

bool BasicBinTile::IsTransparent() const
{
    return false;
}

bool BasicBinTile::CanWalkThrough() const
{
    return false;
}

Item* BasicBinTile::PushItem(Item* i, Direction d, ItemIOInterface* from)
{
    return inventory->AddItem(i);
}

Item* BasicBinTile::PullItem(Direction d, ItemIOInterface* to)
{
    return inventory->PullItem();
}

Tool::ToolType BasicBinTile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float BasicBinTile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string BasicBinTile::GetName() const
{
    return NAME;
}

Tile* BasicBinTile::Clone(World* w, int x, int y, Direction d) const
{
    return new BasicBinTile(w, x, y);
}

const ItemBundle* BasicBinTile::GetMiningResult(Tool* tool) const
{
    return BasicBinTile::DROP->ConstCollapseToItemBundle();
}

void BasicBinTile::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void BasicBinTile::Use(PlayerEntity* user)
{
    TILE_GUI->parentTile = this;
    user->DisplayTileGUI(this, TILE_GUI);
}

void BasicBinTile::Init(nlohmann::json data)
{
    TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
}

BasicBinTile::TileGUI::TileGUI(PlayerEntity* p, BasicBinTile* s)
{
    parentTile = s;
    InventoryGUI* g = p->GetMainInventoryGUI(SCREEN_WIDTH / 2 - (9 * 64), SCREEN_HEIGHT - 128 * 4);
    g->AddDynamicSlot(SCREEN_WIDTH / 2 - 5 * 64, 100, 128, 128, [this]() {
        return &this->GetItemPtrFunc(0);
        }, InventoryGUI::StorageSlotType::GENERIC);
    g->AddDynamicSlot(SCREEN_WIDTH / 2 - 3 * 64, 100, 128, 128, [this]() {
        return &this->GetItemPtrFunc(1);
        }, InventoryGUI::StorageSlotType::GENERIC);
    g->AddDynamicSlot(SCREEN_WIDTH / 2 - 1 * 64, 100, 128, 128, [this]() {
        return &this->GetItemPtrFunc(2);
        }, InventoryGUI::StorageSlotType::GENERIC);
    g->AddDynamicSlot(SCREEN_WIDTH / 2 + 1 * 64, 100, 128, 128, [this]() {
        return &this->GetItemPtrFunc(3);
        }, InventoryGUI::StorageSlotType::GENERIC);
    g->AddDynamicSlot(SCREEN_WIDTH / 2 + 3 * 64, 100, 128, 128, [this]() {
        return &this->GetItemPtrFunc(4);
        }, InventoryGUI::StorageSlotType::GENERIC);
    activeSubGUI = g;
}

Item*& BasicBinTile::TileGUI::GetItemPtrFunc(int i)
{
    return *parentTile->inventory->GetItemPtr(i);
}

void BasicBinTile::TileGUI::PreDrawThisGUI() {
    al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(150, 150, 150, 150));
}

void BasicBinTile::InitForWorld(World* w)
{
    delete TILE_GUI;
    TILE_GUI = new TileGUI(w->GetPlayer(), this);
}

void BasicBinTile::WriteAdditionalDataToFile(std::ofstream& file)
{
    Tile::WriteAdditionalDataToFile(file);
    inventory->SaveToFile(file);
}

void BasicBinTile::LoadAdditionalDataFromFile(std::ifstream& file)
{
    Tile::LoadAdditionalDataFromFile(file);
    inventory = ItemInventory::LoadFromFile(file);
}


BasicBinTile::BasicBinTile(World* w, int x, int y) : Tile(w, x, y)
{
    inventory = new SimpleItemInventory(5);
}


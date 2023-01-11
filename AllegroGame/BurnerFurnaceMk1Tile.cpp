#include "BurnerFurnaceMk1Tile.h"
#include "ResourceLoader.h"
#include "MathUtils.h"
#include <functional>
#include "FuelItem.h"

int BurnerFurnaceMk1Tile::MINING_RESISTANCE;
ToolType BurnerFurnaceMk1Tile::TOOL_TYPE;
std::string BurnerFurnaceMk1Tile::NAME;
BurnerFurnaceMk1Tile::TileGUI* BurnerFurnaceMk1Tile::TILE_GUI;
ALLEGRO_BITMAP* BurnerFurnaceMk1Tile::TEXTURES[2];
ALLEGRO_BITMAP* BurnerFurnaceMk1Tile::BURN_ICON_ON;
ALLEGRO_BITMAP* BurnerFurnaceMk1Tile::BURN_ICON_OFF;
ALLEGRO_BITMAP* BurnerFurnaceMk1Tile::PROGRESS_ICON_ON;
ALLEGRO_BITMAP* BurnerFurnaceMk1Tile::PROGRESS_ICON_OFF;
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

Item* BurnerFurnaceMk1Tile::PushItem(Item* i, Direction d, ItemIOInterface* from)
{
    return input->AddItem(i);
}

Item* BurnerFurnaceMk1Tile::PullItem(Direction d, ItemIOInterface* to)
{
    Item* r = output->GetItem(0);
    output->SetItem(0, nullptr);
    return r;
}

void BurnerFurnaceMk1Tile::Use(PlayerEntity* user)
{
    TILE_GUI->parentTile = this;
    user->DisplayTileGUI(this, TILE_GUI);

}

ToolType BurnerFurnaceMk1Tile::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

float BurnerFurnaceMk1Tile::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string BurnerFurnaceMk1Tile::GetName() const
{
    return NAME;
}

void BurnerFurnaceMk1Tile::WriteAdditionalDataToFile(std::ofstream& file)
{
    file.write(reinterpret_cast<char*>(&burnTimeRemaining),sizeof(float));
    file.write(reinterpret_cast<char*>(&burnTimeFull),sizeof(float));
    file.write(reinterpret_cast<char*>(&progress),sizeof(float));
    input->SaveToFile(file);
    output->SaveToFile(file);
    fuel->SaveToFile(file);
}

void BurnerFurnaceMk1Tile::LoadAdditionalDataFromFile(std::ifstream& file)
{
    file.read(reinterpret_cast<char*>(&burnTimeRemaining), sizeof(float));
    file.read(reinterpret_cast<char*>(&burnTimeFull), sizeof(float));
    file.read(reinterpret_cast<char*>(&progress), sizeof(float));
    input = ItemInventory::LoadFromFile(file);
    output = ItemInventory::LoadFromFile(file);
    fuel = ItemInventory::LoadFromFile(file);
    for (const std::pair<std::string, const SmeltingRecipe*>& r : loaded_smelting_recipes)
        if (r.second->CheckCanPerformOnInventories(input, output))
        {
            currentRecipe = r.second;
            progressPerTick = 1.f / currentRecipe->GetDuration();
            return;
        }
    progressPerTick = 0;
}

void BurnerFurnaceMk1Tile::TickUpdate(uint64_t T)
{
    if (lastT >= T)
        return;
    lastT = T;
    if (currentRecipe == nullptr)
    {
        for (const std::pair<std::string, const SmeltingRecipe*>& r : loaded_smelting_recipes)
            if (r.second->CheckCanPerformOnInventories(input, output))
            {
                currentRecipe = r.second;
                progress = 0;
                progressPerTick = 1.f / currentRecipe->GetDuration();
                break;
            }
    }
    else if (!currentRecipe->CheckCanPerformOnInventories(input, output))
            currentRecipe = nullptr;
    if (burnTimeRemaining <= 0.0000000001)
    {
        FuelItem* f = dynamic_cast<FuelItem*>(fuel->GetItem(0));
        if (f!=nullptr)
        {
            burnTimeRemaining += f->GetBurnTime();
            burnTimeFull = f->GetBurnTime();
            f->RemoveAmount(1);
            if (f->GetAmount() <= 0)
            {
                delete fuel->GetItem(0);
                fuel->SetItem(0,nullptr);
            }
        }
        else
        {
            progress = progressPerTick;
            burnTimeFull = 0;
        }
    }
    else
    {
        burnTimeRemaining-=1;
        if(currentRecipe==nullptr)
            progress = 0;
        else
            progress+=progressPerTick;
        
    }
    if (progress >= .9999999999999)
    {
        if (currentRecipe != nullptr)
        {
            currentRecipe->PerformOnInventories(input, output);
            progress -= 1;
        }
    }
}

bool BurnerFurnaceMk1Tile::DoesTickUpdates() const
{
    return true;
}

void BurnerFurnaceMk1Tile::RegisterLights()
{
    if(burnTimeFull>.0000001)
        world->RegisterLight(World::Light(GetXpos() + .5f, GetYpos() + .5f, BRIGHTNESS));
}

Tile* BurnerFurnaceMk1Tile::Clone(World* w, int x, int y, Direction d) const
{
    return new BurnerFurnaceMk1Tile(w, x, y);
}

const ItemBundle* BurnerFurnaceMk1Tile::GetMiningResult(Tool* tool) const
{
    return DROP->ConstCollapseToItemBundle();
}

void BurnerFurnaceMk1Tile::Draw() const
{
    al_draw_bitmap(TEXTURES[(burnTimeRemaining>0)?1:0], xpos * 128, ypos * 128, 0);
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
    BURN_ICON_OFF = loaded_bitmaps["tex.gui.burn_icon/0"];
    BURN_ICON_ON = loaded_bitmaps["tex.gui.burn_icon/1"];
    PROGRESS_ICON_OFF = loaded_bitmaps["tex.gui.progress_icon/0"];
    PROGRESS_ICON_ON = loaded_bitmaps["tex.gui.progress_icon/1"];
}

void BurnerFurnaceMk1Tile::InitForWorld(World* w)
{
    delete TILE_GUI;
    TILE_GUI = new TileGUI(w->GetPlayer(),this);
}

BurnerFurnaceMk1Tile::BurnerFurnaceMk1Tile(World* w, int x, int y) : Tile(w, x, y), burnTimeRemaining{ 0 }, burnTimeFull{ 0 }
{
    input = new SimpleItemInventory(1);
    fuel = new SimpleItemInventory(1);
    output = new SimpleItemInventory(1);
}

Item*& BurnerFurnaceMk1Tile::TileGUI::InputItemPtrFunc()
{
    return *parentTile->input->GetItemPtr(0);
}

Item*& BurnerFurnaceMk1Tile::TileGUI::FuelItemPtrFunc()
{
    return *parentTile->fuel->GetItemPtr(0);
}

Item*& BurnerFurnaceMk1Tile::TileGUI::OutputItemPtrFunc()
{
    return *parentTile->output->GetItemPtr(0);
}

void BurnerFurnaceMk1Tile::TileGUI::PreDrawThisGUI()
{
    al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(150, 150, 150, 150));
    float by = 128-(parentTile->burnTimeFull? (parentTile->burnTimeRemaining / parentTile->burnTimeFull)*128:0);
    al_draw_bitmap_region(BURN_ICON_OFF, 0, 0, 128, by, SCREEN_WIDTH / 2 - 64, 228, 0);
    al_draw_bitmap_region(BURN_ICON_ON, 0, by, 128, 128 - by, SCREEN_WIDTH / 2 - 64, 228 + by, 0);
    float px = parentTile->progress * 128;
    al_draw_bitmap_region(PROGRESS_ICON_ON, 0, 0, px, 128, SCREEN_WIDTH / 2 - 64, 100, 0);
    al_draw_bitmap_region(PROGRESS_ICON_OFF, px, 0, 128 - px, 128, SCREEN_WIDTH / 2 - 64 + px, 100, 0);
    return;
}

void BurnerFurnaceMk1Tile::TileGUI::PostDrawThisGUI()
{
    ALLEGRO_MOUSE_STATE s;
    al_get_mouse_state(&s);
    FuelItem* f = dynamic_cast<FuelItem*>(parentTile->fuel->GetItem(0));
    if (util_rect_includes_point(SCREEN_WIDTH / 2 - 64, 228, SCREEN_WIDTH / 2 + 64, 356, s.x, s.y))
    {
        al_draw_filled_rectangle(s.x, s.y, s.x + 250, s.y + 80, al_map_rgba(10, 30, 50, 200));
        al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 5, 0, "Burntime for this: %.2fs", parentTile->burnTimeRemaining / TPS);
        al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 30, 0, "Burntime per item: %.2fs", parentTile->burnTimeFull / TPS);
        al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 55, 0, "Max left: %.2fs", ((f?f->GetBurnTime() * f->GetAmount():0) + parentTile->burnTimeRemaining)/TPS);
    }
    else if (util_rect_includes_point(SCREEN_WIDTH / 2 - 64, 100, SCREEN_WIDTH / 2 + 64, 228, s.x, s.y))
    {
        al_draw_filled_rectangle(s.x, s.y, s.x + 250, s.y + 80, al_map_rgba(10, 30, 50, 200));
        if (parentTile->currentRecipe == nullptr)
        {
            al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 5, 0, "Current progress: N/A");
            al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 30, 0, "Progress per second: N/A");
            al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 55, 0, "Time until done: N/As");
        }
        else
        {
            al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 5, 0, "Current progress: %.1f%%", parentTile->progress * 100);
            al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 30, 0, "Progress per second: %.1f%%", parentTile->progressPerTick);
            al_draw_textf(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), s.x + 10, s.y + 55, 0, "Time until done: %.1fs", ((1.f - parentTile->progress) * parentTile->currentRecipe->GetDuration()) / TPS);
        }
    }
}

BurnerFurnaceMk1Tile::TileGUI::TileGUI(PlayerEntity* p, BurnerFurnaceMk1Tile* s)
{
    parentTile = s;
    InventoryGUI* g = p->GetMainInventoryGUI(SCREEN_WIDTH/2-(9*64),SCREEN_HEIGHT-128*4);
    g->AddDynamicSlot(SCREEN_WIDTH/2-320, 100, 128, 128, [this]() {
        return &this->InputItemPtrFunc();
    }, InventoryGUI::StorageSlotType::AUTO_IN_0);
    g->AddDynamicSlot(SCREEN_WIDTH/2-64, 356, 128, 128, [this]() {
        return &this->FuelItemPtrFunc();
        }, InventoryGUI::StorageSlotType::AUTO_FUEL);
    g->AddDynamicSlot(SCREEN_WIDTH/2+192, 100, 128, 128, [this]() {
        return &this->OutputItemPtrFunc();
    }, InventoryGUI::StorageSlotType::AUTO_OUT_0);
    activeSubGUI = g;
}

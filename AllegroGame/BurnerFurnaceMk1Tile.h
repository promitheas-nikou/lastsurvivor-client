#pragma once
#include "Tile.h"
#include "LootBundle.h"
#include "World.h"

#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"

#include "SimpleDynamicItemInventoryGenericStorageSlotUIComponent.h"

class BurnerFurnaceMk1Tile :
    public Tile
{
private:

    class TileGUI:
        public GUI
    {
    public:

        BurnerFurnaceMk1Tile* parentTile;

        Item*& InputItemPtrFunc();
        Item*& FuelItemPtrFunc();
        Item*& OutputItemPtrFunc();

        virtual void PreDrawThisGUI() final;
        virtual void PostDrawThisGUI() final;

        TileGUI(BurnerFurnaceMk1Tile* s);
    };

    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[2];
    static ALLEGRO_BITMAP* BURN_ICON_ON;
    static ALLEGRO_BITMAP* BURN_ICON_OFF;
    static ALLEGRO_BITMAP* PROGRESS_ICON_OFF;
    static ALLEGRO_BITMAP* PROGRESS_ICON_ON;
    static const LootBundle* DROP;
    static float BRIGHTNESS;
    static TileGUI* TILE_GUI;
    float burnTimeRemaining;
    float burnTimeFull;
    float progress;
    float progressPerTick;
    const SmeltingRecipe* currentRecipe;
    ItemInventory* fuel;
    ItemInventory* input;
    ItemInventory* output;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual Item* PushItem(Item* i, Direction d, ItemIOInterface* from) final;
    virtual Item* PullItem(Direction d, ItemIOInterface* to) final;

    virtual void Use(PlayerEntity* user) final;

    virtual ToolType GetOptimalToolType() const final;
    virtual float GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual void WriteAdditionalDataToFile(std::ofstream& file) final;
    virtual void LoadAdditionalDataFromFile(std::ifstream& file) final;

    virtual void TickUpdate(uint64_t T) final;
    virtual bool DoesTickUpdates() const final;

    virtual void RegisterLights() final;

    virtual Tile* Clone(World* w, int x, int y, Direction d) const final;

    void Draw() const final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~BurnerFurnaceMk1Tile() = default;

    BurnerFurnaceMk1Tile(World* w, int x, int y);
};


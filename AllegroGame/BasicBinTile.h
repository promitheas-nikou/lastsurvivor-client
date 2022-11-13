#pragma once
#include "Tile.h"
#include "LootBundle.h"
#include "ItemInventory.h"
#include "InventoryGUI.h"

class BasicBinTile :
    public Tile
{
private:
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;
    static const LootBundle* DROP;
    ItemInventory* inventory;

    class TileGUI :
        public GUI
    {
    public:

        BasicBinTile* parentTile;

        Item*& GetItemPtrFunc(int i);

        virtual void PreDrawThisGUI() final;
        //virtual void PostDrawThisGUI() final;

        TileGUI(PlayerEntity* p, BasicBinTile* s);
    };

    static TileGUI* TILE_GUI;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual Item* PushItem(Item* i, Direction d, ItemIOInterface* from) final;
    virtual Item* PullItem(Direction d, ItemIOInterface* to) final;

    virtual ToolType GetOptimalToolType() const final;
    virtual int GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual Tile* Clone(World* w, int x, int y, Direction d) const final;

    void Draw() const final;

    virtual void Use(PlayerEntity* user) final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual void InitForWorld(World* w) final;

    virtual void WriteAdditionalDataToFile(std::ofstream& file) final;
    virtual void LoadAdditionalDataFromFile(std::ifstream& file) final;

    virtual ~BasicBinTile() = default;

    BasicBinTile(World* w, int x, int y);
};


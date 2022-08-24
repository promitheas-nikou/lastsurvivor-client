#pragma once
#include "Tile.h"
#include "LootBundle.h"
#include "World.h"

class BurnerFurnaceMk1Tile :
    public Tile
{
private:

    class TileGUI:
        public GUI
    {
    public:
        virtual void PreDrawThisGUI() final;
        virtual void PostDrawThisGUI() final;

        TileGUI(PlayerEntity* p);
    };

    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[2];
    static const LootBundle* DROP;
    static float BRIGHTNESS;
    static GUI* TILE_GUI;
    float burnTimeRemaining;
    Item* fuel;
    Item* input;
    Item* output;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual void Use(PlayerEntity* user) final;

    virtual ToolType GetOptimalToolType() const final;
    virtual int GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual void RegisterLights() final;

    virtual Tile* Clone(World* w, int x, int y) const final;

    void Draw() const final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~BurnerFurnaceMk1Tile() = default;

    BurnerFurnaceMk1Tile(World* w, int x, int y);
};


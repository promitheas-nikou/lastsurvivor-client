#pragma once
#include "Tile.h"
#include "LootBundle.h"
class WheatCropTile :
    public Tile
{
private:
    static constexpr int MAX_GROWTH_STAGES = 5;
    static constexpr int TICKS_PER_STAGE = 10;
    static constexpr int TICKS_UNTIL_GROWN = (MAX_GROWTH_STAGES - 1) * TICKS_PER_STAGE;
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[MAX_GROWTH_STAGES];
    static const LootBundle* DROPS[2];
    mutable int age;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual ToolType GetOptimalToolType() const final;
    virtual float GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual void RandomTickUpdate() final;

    virtual Tile* Clone(World* w, int x, int y, Direction d) const final;

    void Draw() const final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~WheatCropTile() = default;

    WheatCropTile(World* w, int x, int y);
};


		
#pragma once
#include "Tile.h"
class BerryBushTile :
    public Tile
{
private:
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[2];
    static const ItemBundle* DROP;

    int growthTimer;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual ToolType GetOptimalToolType() const final;
    virtual int GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual Tile* Clone(World* w, int x, int y) const final;

    void Draw() const final;

    virtual void Use(PlayerEntity* p) override;

    void RandomTickUpdate() final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~BerryBushTile() = default;

    BerryBushTile(World* w, int x, int y);
};


#pragma once
#include "Tile.h"
#include "LootBundle.h"

class TreeTile :
    public Tile
{
private:
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[4];
    static const LootBundle* DROP;

    int growthTimer;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual ToolType GetOptimalToolType() const final;
    virtual float GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual Tile* Clone(World* w, int x, int y, Direction d) const final;

    void Draw() const final;

    void RandomTickUpdate() final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~TreeTile() = default;

    TreeTile(World* w, int x, int y);
    TreeTile(World* w, int x, int y, int g);
};


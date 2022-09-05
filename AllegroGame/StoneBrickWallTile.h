#pragma once
#include "Tile.h"
#include "LootBundle.h"
class StoneBrickWallTile :
    public Tile
{
private:
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;
    static const LootBundle* DROP;
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

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~StoneBrickWallTile() = default;

    StoneBrickWallTile(World* w, int x, int y);
};


		
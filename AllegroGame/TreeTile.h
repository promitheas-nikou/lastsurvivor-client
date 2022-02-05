#pragma once
#include "Tile.h"
class TreeTile :
    public Tile
{
private:
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[4];

    int growthTimer;
public:
    static const std::string ID;
    std::string GetID() const final;

    bool IsTransparent() const final;

    void Draw() const final;

    void RandomTickUpdate() final;

    static void Init(nlohmann::json data);

    TreeTile(World* w, int x, int y);
};


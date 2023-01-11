#pragma once

#include "PlaceableItem.h"
#include "json.h"

class BrickWallItem :
    public PlaceableItem
{
private:
    static std::string NAME;
    static std::string TILE_ID;
    static std::string DESCRIPTION;
    static ALLEGRO_BITMAP* TEXTURE;

public:

    static const std::string ID;

    std::string GetID() const final;

    virtual Tile* GetTile(World* w, int x, int y, Direction d) override;

    virtual Item* Clone() const override;

    BrickWallItem();

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~BrickWallItem() = default;

};


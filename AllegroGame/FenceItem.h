#pragma once

#include "PlaceableItem.h"
#include "json.h"

class FenceItem :
    public PlaceableItem
{
private:
    static std::string NAME;
    static std::string DESCRIPTION;
    static ALLEGRO_BITMAP* TEXTURE;

public:

    static const std::string ID;

    std::string GetID() const final;

    virtual Tile* GetTile(World* w, int x, int y) override;

    virtual Item* Clone() const override;

    FenceItem();

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~FenceItem() = default;

};


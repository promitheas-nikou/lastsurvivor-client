#pragma once

#include "Item.h"

class MagnetiteChunkItem :
    public Item
{
private:
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;

public:

    static const std::string ID;

    std::string GetID() const final;

    MagnetiteChunkItem();

    virtual Item* Clone() const override;

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~MagnetiteChunkItem() = default;

};


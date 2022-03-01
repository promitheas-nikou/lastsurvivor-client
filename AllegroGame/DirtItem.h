#pragma once

#include "Item.h"
#include "json.h"

class DirtItem :
    public Item
{
private:
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;

public:

    static const std::string ID;

    std::string GetID() const final;

    virtual Item* Clone() const override;

    DirtItem();

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

};


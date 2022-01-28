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

    static const int ID = 2;

    int GetID() const final;

    DirtItem();

    ALLEGRO_BITMAP* GetTexture() const final;

    static void Init(nlohmann::json data);

};


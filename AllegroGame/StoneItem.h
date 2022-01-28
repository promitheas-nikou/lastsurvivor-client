#pragma once

#include "Item.h"
#include "json.h"

class StoneItem :
    public Item
{
private:
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;

public:

    static const int ID = 3;

    int GetID() const final;

    StoneItem();

    ALLEGRO_BITMAP* GetTexture() const final;

    static void Init(nlohmann::json data);

};


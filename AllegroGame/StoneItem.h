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

    static const int ID = 1;

    int GetID() const final;

    StoneItem();

    static void Init(nlohmann::json data);

};


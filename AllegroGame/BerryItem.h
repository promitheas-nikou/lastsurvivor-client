#pragma once
#include "SimpleConsumableItem.h"

class BerryItem :
    public SimpleConsumableItem
{
private:
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;
    static float HEALTH;
    static float HUNGER;
    static float WATER;
public:

    static const std::string ID;

    std::string GetID() const final;

    virtual Item* Clone() const override;

    BerryItem();

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~BerryItem() = default;
};


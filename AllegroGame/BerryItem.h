#pragma once
#include "ConsumableItem.h"

class BerryItem :
    public ConsumableItem
{
private:
    static std::string NAME;
    static std::string DESCRIPTION;
    static ALLEGRO_BITMAP* TEXTURE;
    static float HEALTH;
    static float HUNGER;
    static float WATER;
public:

    static const std::string ID;

    std::string GetID() const final;

    virtual Item* Clone() const override;

    virtual float GetHealthBoost() const final;
    virtual float GetFoodBoost() const final;
    virtual float GetWaterBoost() const final;

    BerryItem();

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~BerryItem() = default;
};


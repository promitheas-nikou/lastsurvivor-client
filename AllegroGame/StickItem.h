#pragma once

#include "FuelItem.h"

class StickItem :
    public FuelItem
{
private:
    static std::string NAME;
    static std::string DESCRIPTION;
    static ALLEGRO_BITMAP* TEXTURE;
    static float BURN_TIME;
    static float BURN_HEAT;

public:

    static const std::string ID;

    std::string GetID() const final;

    StickItem();

    virtual float GetBurnTime() const final;
    virtual float GetBurnHeat() const final;

    virtual Item* Clone() const override;

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~StickItem() = default;
};


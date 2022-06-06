#pragma once
#include "FuelItem.h"
class CoalItem :
    public FuelItem
{
private:
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;
    static float BURN_TIME;

public:

    static const std::string ID;

    std::string GetID() const final;

    virtual Item* Clone() const override;

    virtual float GetBurnTime() const final;

    CoalItem();

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~CoalItem() = default;

};


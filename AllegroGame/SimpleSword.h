#pragma once
#include "SimpleMeleeWeaponItem.h"
#include <string>

class SimpleSword :
    public SimpleMeleeWeaponItem
{
private:
    static std::string NAME;
    static float DAMAGE;
    static ALLEGRO_BITMAP* TEXTURE;

public:

    static const std::string ID;

    std::string GetID() const final;

    SimpleSword();

    virtual Item* Clone() const override;

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~SimpleSword() = default;
};


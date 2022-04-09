#pragma once
#include "RangedWeaponItem.h"

class GunItem :
    public RangedWeaponItem
{
private:
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;
    static ALLEGRO_BITMAP* BULLET_TEXTURE;
    static float DAMAGE;
    static float FIRE_SPEED;

public:

    static const std::string ID;

    std::string GetID() const final;

    virtual void Fire(World* world, float xpos, float ypos, float rot, Entity* owner = nullptr) final;

    GunItem();

    virtual Item* Clone() const override;

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~GunItem() = default;
};


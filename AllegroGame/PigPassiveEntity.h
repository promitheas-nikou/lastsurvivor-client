#pragma once
#include "PassiveEntity.h"
#include "json.h"
#include "LootBundle.h"

class PigPassiveEntity :
    public PassiveEntity
{
private:
    static float SPEED;
    static float MAX_HEALTH;
    static float MASS;
    static ALLEGRO_BITMAP* TEXTURE;
    static const LootBundle* DROP;
    static std::string NAME;
public:
    static const std::string ID;
    virtual Entity* Clone(World* world, float x, float y) const override;
    virtual void Tick() override;
    virtual void Draw() override;
    virtual std::string GetID() const final;

    virtual ItemBundle* GetKillingDrops() const final;

    static void Init(nlohmann::json data);

    PigPassiveEntity(World* world, float xpos, float ypos);
};


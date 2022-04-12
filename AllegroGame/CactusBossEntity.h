#pragma once
#include "HostileEntity.h"
#include "json.h"
#include "RattleLauncher.h"

class CactusBossEntity :
    public HostileEntity
{
private:
    float speed = .0025f;
    float reachmel = 1.f;
    float reachran = 49.f;
    int graphicsCounter;
    static float MAX_HEALTH;
    static ALLEGRO_BITMAP* LEFT_TEXTURES[5];
    static ALLEGRO_BITMAP* FRONT_TEXTURES[5];
    static ALLEGRO_BITMAP* RIGHT_TEXTURES[5];
    RattleLauncher* rl;
public:
    static const std::string ID;
    virtual void Tick() override;
    virtual void Draw() override;
    virtual std::string GetID() const final;
    static void Init(nlohmann::json data);

    CactusBossEntity(World* world, float xpos, float ypos);
};


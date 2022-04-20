#pragma once
#include "HostileEntity.h"
#include "json.h"

class ZombieEntity :
    public HostileEntity
{
private:
    static float SPEED;
    static float DAMAGE;
    static float REACHSQ;
    static ALLEGRO_BITMAP* TEXTURE;
    static std::string NAME;
public:
    static const std::string ID;
    virtual void Tick() override;
    virtual void Draw() override;
    virtual std::string GetID() const final;

    static void Init(nlohmann::json data);

    ZombieEntity(World* world, float xpos, float ypos);
};


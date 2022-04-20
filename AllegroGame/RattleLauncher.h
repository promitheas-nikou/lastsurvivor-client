#pragma once
#include "RangedWeapon.h"
#include "json.h"
#include <string>
#include <allegro5/allegro5.h>
#include "AudioMultiTrackCollection.h"

class RattleLauncher :
    public RangedWeapon
{
private:
    static ALLEGRO_BITMAP* BULLET_TEXTURES[8];
    static float DAMAGE;
    static float FIRE_SPEED;
    static AudioMultiTrackCollection AUDIO_TRACKS;

public:

    static const std::string ID;

    virtual void Fire(World* world, float xpos, float ypos, float rot, Entity* owner = nullptr) final;

    RattleLauncher() = default;

    static void Init(nlohmann::json data);

    virtual ~RattleLauncher() = default;
};


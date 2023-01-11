#pragma once
#include "HostileEntity.h"
#include "json.h"
#include "Projectile.h"
#include "AudioMultiTrackCollection.h"

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
public:


    class RattleProjectile :
        public Projectile
    {
    private:
        static ALLEGRO_BITMAP* BULLET_TEXTURES[8];
        static float DAMAGE;
        static float FIRE_SPEED;
        static AudioMultiTrackCollection AUDIO_TRACKS;
        char animCounter;

    public:

        static const std::string ID;

        virtual std::string GetID() const final;

        virtual void Draw() override;

        virtual Entity* Clone(World* w, float x, float y) const override;

        virtual void Tick() override;

        RattleProjectile(World* w, float angle, float xpos, float ypos);
        RattleProjectile(World* w, float xpos, float ypos);

        static void Init(nlohmann::json data);

        virtual void PlaySound(SoundType st) final;

        virtual ~RattleProjectile() = default;
    };

    virtual Entity* Clone(World* world, float x, float y) const override;
    static const std::string ID;
    virtual void Tick() override;
    virtual void Draw() override;
    virtual std::string GetID() const final;
    static void Init(nlohmann::json data);

    CactusBossEntity(World* world, float xpos, float ypos);
};


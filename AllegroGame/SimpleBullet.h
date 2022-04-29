#pragma once
#include "Bullet.h"
#include <allegro5/allegro5.h>
#include "AudioMultiTrackCollection.h"

class SimpleBullet :
    public Bullet
{
private:
    ALLEGRO_BITMAP** textures;
    size_t len;
    size_t counter;
    size_t tpf;
    float damage;
    std::function<void(Entity*)> collisionCallback;
    AudioMultiTrackCollection* AUDIO_TRACKS;
protected:
    virtual void CollisionCallback(Entity* e) override;
public:

    void SetCollisionCallback(std::function<void(Entity*)> c);

    static const std::string ID;

    virtual std::string GetID() const final;

    virtual void Tick() override;

    SimpleBullet(World* w, float dmg, float x, float y, float velx, float vely, ALLEGRO_BITMAP** tex, size_t len, size_t tpf, AudioMultiTrackCollection* col);

    virtual float GetDamage() const override;

    virtual void PlaySound(SoundType t) const final;

    void Draw() override;

    virtual ~SimpleBullet() = default;
};


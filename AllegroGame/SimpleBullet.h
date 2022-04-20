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
    float damage;
    AudioMultiTrackCollection* AUDIO_TRACKS;
public:
    static const std::string ID;

    virtual std::string GetID() const final;

    virtual void Tick() override;

    SimpleBullet(World* w, float dmg, float x, float y, float velx, float vely, ALLEGRO_BITMAP** tex, size_t len, AudioMultiTrackCollection* col);

    virtual float GetDamage() const override;

    virtual void PlaySound(SoundType t) const final;

    void Draw() override;

    virtual ~SimpleBullet() = default;
};


#pragma once
#include "Bullet.h"
#include <allegro5/allegro5.h>

class SimpleBullet :
    public Bullet
{
private:
    ALLEGRO_BITMAP* texture;
public:
    static const std::string ID;

    virtual std::string GetID() const final;

    SimpleBullet(World* w, float dmg, float x, float y, float velx, float vely, ALLEGRO_BITMAP* tex);

    void Draw() override;

    virtual ~SimpleBullet() = default;
};


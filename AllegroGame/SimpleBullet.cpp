#include "SimpleBullet.h"

const std::string SimpleBullet::ID = "entities.bullet";

SimpleBullet::SimpleBullet(World* w, float dmg, float x, float y, float velx, float vely, ALLEGRO_BITMAP** tex, size_t len) : Bullet(w, x, y, velx, vely), textures{ tex }, damage{ dmg }, len{ len }
{}

float SimpleBullet::GetDamage() const
{
    return damage;
}


void SimpleBullet::Draw()
{
    int x = floor((GetXpos() - getXsize() / 2) * 128);
    int y = floor((GetYpos() - getYsize() / 2) * 128);
    al_draw_bitmap(textures[counter], x, y, 0);
}

std::string SimpleBullet::GetID() const
{
    return ID;
}

void SimpleBullet::Tick()
{
    Bullet::Tick();
    counter = (counter + 1) % len;
}

#include "SimpleBullet.h"

const std::string SimpleBullet::ID = "entities.bullet";

SimpleBullet::SimpleBullet(World* w, float dmg, float x, float y, float velx, float vely, ALLEGRO_BITMAP* tex) : Bullet(w, dmg, x, y, velx, vely), texture{ tex }
{}


void SimpleBullet::Draw()
{
    int x = floor((GetXpos()) * 128);
    int y = floor((GetYpos()) * 128);
    al_draw_bitmap(texture, x, y, 0);
}

std::string SimpleBullet::GetID() const
{
    return ID;
}

#include "SimpleBullet.h"

const std::string SimpleBullet::ID = "entities.bullet";

SimpleBullet::SimpleBullet(World* w, float dmg, float x, float y, float velx, float vely, ALLEGRO_BITMAP** tex, size_t len, AudioMultiTrackCollection* col) : Bullet(w, x, y, velx, vely), textures{ tex }, damage{ dmg }, len{ len }, AUDIO_TRACKS{ col }
{
    if(col!=nullptr)
        col->Play(SoundType::PROJECTILE_LAUNCH);
}

float SimpleBullet::GetDamage() const
{
    return damage;
}

void SimpleBullet::PlaySound(SoundType t) const
{
    if(AUDIO_TRACKS!=nullptr)
        AUDIO_TRACKS->Play(t);
}


void SimpleBullet::Draw()
{
    int x = floor(GetXpos() * 128);
    int y = floor(GetYpos() * 128);
    al_draw_rotated_bitmap(textures[counter], al_get_bitmap_width(textures[counter]) / 2, al_get_bitmap_width(textures[counter]) / 2, x, y, 0, 0);
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

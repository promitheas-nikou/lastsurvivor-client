#include "CactusBossEntity.h"
#include "ZombieEntity.h"
#include "ResourceLoader.h"
#include "World.h"
#include "RangedWeapon.h"
#define _USE_MATH_DEFINES
#include <math.h>

const std::string CactusBossEntity::ID = "entities.cactus_boss";
float CactusBossEntity::MAX_HEALTH;
ALLEGRO_BITMAP* CactusBossEntity::LEFT_TEXTURES[5];
ALLEGRO_BITMAP* CactusBossEntity::FRONT_TEXTURES[5];
ALLEGRO_BITMAP* CactusBossEntity::RIGHT_TEXTURES[5];

Entity* CactusBossEntity::Clone(World* world, float x, float y) const
{
	return new CactusBossEntity(world, x, y);
}

void CactusBossEntity::Tick()
{
	graphicsCounter = (graphicsCounter + 1) % 40;
	float xdif = GetXpos() - containingWorld->GetPlayer()->GetXpos();
	float ydif = GetYpos() - containingWorld->GetPlayer()->GetYpos();
	float angle = atan2f(ydif, xdif) - M_PI_2;
	SetRotation(angle);
	Entity::ApplyForce(speed * cosf(angle), speed * sinf(angle));
	HostileEntity::Tick();
	if (CooldownReady())
		if (containingWorld->GetPlayer()->CollidesWith(this))
		{
			containingWorld->GetPlayer()->DoDamage(10.f);
			ResetCooldown(30);
		}
		else if (xdif * xdif + ydif * ydif < reachran)
		{
			containingWorld->AddEntity(new RattleProjectile(containingWorld, GetRotation() , GetXpos(), GetYpos()));
			ResetCooldown(60);
		}

}

void CactusBossEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	int ind;
	if (graphicsCounter < 0)
		ind = 4;
	else
		ind = graphicsCounter/10;
	if (GetRotation() < M_PI_4)
		al_draw_rotated_bitmap(LEFT_TEXTURES[ind], al_get_bitmap_width(LEFT_TEXTURES[ind]) / 2, al_get_bitmap_height(LEFT_TEXTURES[ind]) / 2, x, y, 0, 0);
	else if (GetRotation() < 3 * M_PI_4)
		al_draw_rotated_bitmap(FRONT_TEXTURES[ind], al_get_bitmap_width(LEFT_TEXTURES[ind]) / 2, al_get_bitmap_height(LEFT_TEXTURES[ind]) / 2, x, y, 0, 0);
	else if (GetRotation() < 3 * M_PI_2)
		al_draw_rotated_bitmap(RIGHT_TEXTURES[ind], al_get_bitmap_width(LEFT_TEXTURES[ind])/2, al_get_bitmap_height(LEFT_TEXTURES[ind])/2, x, y, 0, 0);
	else
		al_draw_rotated_bitmap(LEFT_TEXTURES[ind], al_get_bitmap_width(LEFT_TEXTURES[ind]) / 2, al_get_bitmap_height(LEFT_TEXTURES[ind]) / 2, x, y, 0, 0);
}

std::string CactusBossEntity::GetID() const
{
	return ID;
}

void CactusBossEntity::Init(nlohmann::json data)
{
	int i;
	i = 0;
	for (std::string id : data["textures_left"])
		LEFT_TEXTURES[i++] = game_GetTexture(id);
	i = 0;
	for (std::string id : data["textures_front"])
		FRONT_TEXTURES[i++] = game_GetTexture(id);
	i = 0;
	for (std::string id : data["textures_right"])
		RIGHT_TEXTURES[i++] = game_GetTexture(id);
	MAX_HEALTH = data[DATA_JSON_MAX_HEALTH_KEY];
}

CactusBossEntity::CactusBossEntity(World* world, float xpos, float ypos) : HostileEntity(world, xpos, ypos, MAX_HEALTH, 10.f, 0.f, 0.f, 3.0f, 3.0f), graphicsCounter{ 0 }
{
	SetName("Cactus Boss");
}

ALLEGRO_BITMAP* CactusBossEntity::RattleProjectile::BULLET_TEXTURES[8];
float CactusBossEntity::RattleProjectile::DAMAGE;
float CactusBossEntity::RattleProjectile::FIRE_SPEED;
AudioMultiTrackCollection CactusBossEntity::RattleProjectile::AUDIO_TRACKS;
const std::string CactusBossEntity::RattleProjectile::ID = "entities.projectiles.cactus_boss_rattle";

std::string CactusBossEntity::RattleProjectile::GetID() const
{
	return ID;
}

void CactusBossEntity::RattleProjectile::Draw()
{

	int x = floor((GetXpos()) * 128);
	int y = floor((GetYpos()) * 128);
	ALLEGRO_BITMAP* b = BULLET_TEXTURES[animCounter / 10];
	int w = al_get_bitmap_width(b);
	int h = al_get_bitmap_height(b);
	al_draw_rotated_bitmap(b, w/2, h/2, x, y, GetRotation(), 0);

}

Entity* CactusBossEntity::RattleProjectile::Clone(World* w, float x, float y) const
{
	return new RattleProjectile(w,0,x,y);
}

void CactusBossEntity::RattleProjectile::Tick()
{
	Projectile::Tick();
	animCounter = (animCounter + 1) % 80;
	//printf("%.3f:%.3f\n", GetXpos(), GetYpos());
	for(Entity* e: containingWorld->GetEntitiesColliding(this))
		if ((e->GetID() != CactusBossEntity::ID) && (e->GetID()!=RattleProjectile::ID))
		{
			e->DoDamage(DAMAGE);
			e->ApplyForce(GetMass() * GetXvel(), GetMass() * GetYvel());
			PlaySound(SoundType::PROJECTILE_HIT);
			Kill();
			return;
		}
}

CactusBossEntity::RattleProjectile::RattleProjectile(World* w, float angle, float xpos, float ypos): Projectile(w, xpos, ypos, .03f* (-sinf(-angle)), .03f* (-cosf(-angle)), angle)
{
	SetHasFriction(false);
	SetKillOnCollision(true);
	SetName("Rattle");
}

CactusBossEntity::RattleProjectile::RattleProjectile(World* w, float xpos, float ypos) : RattleProjectile(w, 0.f, xpos, ypos)
{}

void CactusBossEntity::RattleProjectile::Init(nlohmann::json data)
{
	int i = 0;
	for (std::string s : data[DATA_JSON_TEXTURE_LIST_KEY])
		BULLET_TEXTURES[i++] = game_GetTexture(s);
	DAMAGE = data[DATA_JSON_DAMAGE_KEY];
	FIRE_SPEED = data[DATA_JSON_FIRE_SPEED_KEY];
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

void CactusBossEntity::RattleProjectile::PlaySound(SoundType st)
{
	AUDIO_TRACKS.Play(st);
}

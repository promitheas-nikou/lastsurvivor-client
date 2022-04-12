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

void CactusBossEntity::Tick()
{
	graphicsCounter = (graphicsCounter + 1) % 40;
	float xdif = GetXpos() - containingWorld->GetPlayer()->GetXpos();
	float ydif = GetYpos() - containingWorld->GetPlayer()->GetYpos();
	float angle = 3.14159265358979f + atan2f(ydif, xdif);
	SetRotation(angle);
	Entity::applyForce(speed * cosf(angle), speed * sinf(angle));
	HostileEntity::Tick();
	if (CooldownReady())
		if (xdif * xdif + ydif * ydif < reachmel)
		{
			containingWorld->GetPlayer()->DoDamage(10.f);
			ResetCooldown(30);
		}
		else if (xdif * xdif + ydif * ydif < reachran)
		{
			rl->Fire(containingWorld, GetXpos(), GetYpos(), angle, this);
			ResetCooldown(60);
		}

}

void CactusBossEntity::Draw()
{
	int x = floor((GetXpos() - getXsize() / 2) * 128);
	int y = floor((GetYpos() - getYsize() / 2) * 128);
	int ind;
	if (graphicsCounter < 0)
		ind = 4;
	else
		ind = graphicsCounter/10;
	if (getRotation() < M_PI_4)
		al_draw_bitmap(RIGHT_TEXTURES[ind], x, y, 0);
	else if (getRotation() < 3 * M_PI_4)
		al_draw_bitmap(FRONT_TEXTURES[ind], x, y, 0);
	else if (getRotation() < 3 * M_PI_2)
		al_draw_bitmap(LEFT_TEXTURES[ind], x, y, 0);
	else
		al_draw_bitmap(RIGHT_TEXTURES[ind], x, y, 0);
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
		LEFT_TEXTURES[i++] = loaded_bitmaps[id];
	i = 0;
	for (std::string id : data["textures_front"])
		FRONT_TEXTURES[i++] = loaded_bitmaps[id];
	i = 0;
	for (std::string id : data["textures_right"])
		RIGHT_TEXTURES[i++] = loaded_bitmaps[id];
	RattleLauncher::Init(data["rattle_launcher"]);
}

CactusBossEntity::CactusBossEntity(World* world, float xpos, float ypos) : HostileEntity(world, xpos, ypos, 300.f, 10.f, 0.f, 0.f, 3.0f, 3.0f), graphicsCounter{ 0 }
{
	rl = new RattleLauncher();
	SetName("Cactus Boss");
}

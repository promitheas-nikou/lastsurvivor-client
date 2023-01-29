#include "ZombieEntity.h"
#include "ResourceLoader.h"
#include "World.h"
#include "MathUtils.h"

float ZombieEntity::SPEED;
float ZombieEntity::DAMAGE;
float ZombieEntity::REACHSQ;
ALLEGRO_BITMAP* ZombieEntity::TEXTURE;
std::string ZombieEntity::NAME;
const std::string ZombieEntity::ID = "entities.zombie";

Entity* ZombieEntity::Clone(World* world, float x, float y) const
{
	return new ZombieEntity(world, x, y);
}

void ZombieEntity::Tick()
{	
	float xdif = GetXpos() - containingWorld->GetPlayer()->GetXpos();
	float ydif = GetYpos() - containingWorld->GetPlayer()->GetYpos();
	float angle = atan2f(ydif, xdif) - M_PI_2;
	SetRotation(angle);
	Entity::ApplyForceRotated(SPEED);
	HostileEntity::Tick();
	if(CooldownReady())
		if (xdif * xdif + ydif * ydif < REACHSQ)
		{
			containingWorld->GetPlayer()->DoDamage(DAMAGE);
			ResetCooldown(50);
		}
}

void ZombieEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(TEXTURE, 64, 64, x, y, GetRotation(), 0);
}

std::string ZombieEntity::GetID() const
{
	return ID;
}

void ZombieEntity::Init(nlohmann::json data)
{
	SPEED = data[DATA_JSON_SPEED_KEY];
	DAMAGE = data[DATA_JSON_DAMAGE_KEY];
	REACHSQ = data[DATA_JSON_RANGESQ_KEY];
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}

ZombieEntity::ZombieEntity(World* world, float xpos, float ypos) : HostileEntity(world, xpos, ypos, 100.f, 1.f, 0.f, 0.f, .5f, .5f)
{
	SetName("Zombie");
}

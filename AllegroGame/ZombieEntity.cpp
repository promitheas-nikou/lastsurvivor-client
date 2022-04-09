#include "ZombieEntity.h"
#include "ResourceLoader.h"
#include "World.h"

const std::string ZombieEntity::ID = "entities.zombie";

void ZombieEntity::Tick()
{	
	float xdif = GetXpos() - containingWorld->GetPlayer()->GetXpos();
	float ydif = GetYpos() - containingWorld->GetPlayer()->GetYpos();
	float angle = 3.14159265358979f+atan2f(ydif, xdif);
	SetRotation(angle);
	Entity::applyForce(speed * cosf(angle), speed * sinf(angle));
	HostileEntity::Tick();
	if(CooldownReady())
		if (xdif * xdif + ydif * ydif < reach)
		{
			containingWorld->GetPlayer()->DoDamage(5.f);
			ResetCooldown(25);
		}
}

void ZombieEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(loaded_bitmaps["tex.entities.zombie"], 64, 64, x, y, getRotation()+3.14159265358f/2, 0);
}

std::string ZombieEntity::GetID() const
{
	return ID;
}

ZombieEntity::ZombieEntity(World* world, float xpos, float ypos) : HostileEntity(world, xpos, ypos, 100.f, 1.f, 0.f, 0.f, .5f, .5f)
{
	SetName("Zombie");
}

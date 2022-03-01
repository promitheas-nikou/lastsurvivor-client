#include "SimpleHostileEntity.h"
#include "ResourceLoader.h"
#include "World.h"

void SimpleHostileEntity::Tick()
{	
	Entity::Tick();
	float xdif = GetXpos() - containingWorld->GetPlayer()->GetXpos();
	float ydif = GetYpos() - containingWorld->GetPlayer()->GetYpos();
	float angle = 3.14159265358979f+atan2f(ydif, xdif);
	SetRotation(angle);
	Entity::applyForce(speed * cosf(angle), speed * sinf(angle));
}

void SimpleHostileEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(loaded_bitmaps["tex.entities.player"], 64, 64, x, y, getRotation()+3.14159265358f/2, 0);
}

SimpleHostileEntity::SimpleHostileEntity(World* world, float xpos, float ypos) : HostileEntity(world, xpos, ypos, 100.f)
{
}

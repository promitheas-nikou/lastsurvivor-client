#include "SheepPassiveEntity.h"
#include "ResourceLoader.h"

const std::string SheepPassiveEntity::ID = "entities.sheep";

float SheepPassiveEntity::SPEED;
float SheepPassiveEntity::MAX_HEALTH;
float SheepPassiveEntity::MASS;
ALLEGRO_BITMAP* SheepPassiveEntity::TEXTURE;
std::string SheepPassiveEntity::NAME;

Entity* SheepPassiveEntity::Clone(World* world, float x, float y) const
{
	return new SheepPassiveEntity(world, x, y);
}

void SheepPassiveEntity::Tick()
{
	PassiveEntity::Tick();
}

void SheepPassiveEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(TEXTURE, 64, 64, x, y, GetRotation(), 0);
}

std::string SheepPassiveEntity::GetID() const
{
	return ID;
}

void SheepPassiveEntity::Init(nlohmann::json data)
{
	SPEED = data[DATA_JSON_SPEED_KEY];
	MASS = data[DATA_JSON_MASS_KEY];
	MAX_HEALTH = data[DATA_JSON_MAX_HEALTH_KEY];
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

SheepPassiveEntity::SheepPassiveEntity(World* world, float xpos, float ypos) : PassiveEntity(world, xpos, ypos, 50, 1, 0, 0)
{
	SetName(NAME);
	minTime = 50;
	maxTime = 200;
	forceApplied = SPEED;
}

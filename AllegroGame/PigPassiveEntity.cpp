#include "PigPassiveEntity.h"
#include "ResourceLoader.h"

const std::string PigPassiveEntity::ID = "entities.pig";

float PigPassiveEntity::SPEED;
float PigPassiveEntity::MAX_HEALTH;
float PigPassiveEntity::MASS;
ALLEGRO_BITMAP* PigPassiveEntity::TEXTURE;
std::string PigPassiveEntity::NAME;

Entity* PigPassiveEntity::Clone(World* world, float x, float y) const
{
	return new PigPassiveEntity(world, x, y);
}

void PigPassiveEntity::Tick()
{
	PassiveEntity::Tick();
}

void PigPassiveEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(TEXTURE, 64, 64, x, y, GetRotation(), 0);
}

std::string PigPassiveEntity::GetID() const
{
	return ID;
}

void PigPassiveEntity::Init(nlohmann::json data)
{
	SPEED = data[DATA_JSON_SPEED_KEY];
	MASS = data[DATA_JSON_MASS_KEY];
	MAX_HEALTH = data[DATA_JSON_MAX_HEALTH_KEY];
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

PigPassiveEntity::PigPassiveEntity(World* world, float xpos, float ypos) : PassiveEntity(world, xpos, ypos, 50, 1, 0, 0)
{
	SetName(NAME);
	minTime = 50;
	maxTime = 200;
	forceApplied = SPEED;
}

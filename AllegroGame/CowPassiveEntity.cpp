#include "CowPassiveEntity.h"
#include "ResourceLoader.h"

const std::string CowPassiveEntity::ID = "entities.cow";

float CowPassiveEntity::SPEED;
float CowPassiveEntity::MAX_HEALTH;
float CowPassiveEntity::MASS;
ALLEGRO_BITMAP* CowPassiveEntity::TEXTURE;
std::string CowPassiveEntity::NAME;

Entity* CowPassiveEntity::Clone(World* world, float x, float y) const
{
	return new CowPassiveEntity(world, x, y);
}

void CowPassiveEntity::Tick()
{
	PassiveEntity::Tick();
}

void CowPassiveEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(TEXTURE, 64, 64, x, y, GetRotation(), 0);
}

std::string CowPassiveEntity::GetID() const
{
	return ID;
}

void CowPassiveEntity::Init(nlohmann::json data)
{
	SPEED = data[DATA_JSON_SPEED_KEY];
	MASS = data[DATA_JSON_MASS_KEY];
	MAX_HEALTH = data[DATA_JSON_MAX_HEALTH_KEY];
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}

CowPassiveEntity::CowPassiveEntity(World* world, float xpos, float ypos) : PassiveEntity(world, xpos, ypos, 50, 1, 0, 0)
{
	SetName(NAME);
	minTime = 50;
	maxTime = 200;
	forceApplied = SPEED;
}

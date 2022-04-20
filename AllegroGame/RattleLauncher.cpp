#include "RattleLauncher.h"
#include "SimpleBullet.h"
#include "World.h"
#include "ResourceLoader.h"


ALLEGRO_BITMAP* RattleLauncher::BULLET_TEXTURES[8];
float RattleLauncher::DAMAGE;
float RattleLauncher::FIRE_SPEED;
AudioMultiTrackCollection RattleLauncher::AUDIO_TRACKS;

void RattleLauncher::Fire(World* world, float xpos, float ypos, float rot, Entity* owner)
{
	SimpleBullet* b = new SimpleBullet(world, DAMAGE, xpos, ypos, FIRE_SPEED * cosf(rot), FIRE_SPEED * sinf(rot), BULLET_TEXTURES, 8, &AUDIO_TRACKS);
	b->SetOwnerEntity(owner);
	world->AddEntity(b);
}

void RattleLauncher::Init(nlohmann::json data)
{
	int i = 0;
	for(std::string s: data[DATA_JSON_TEXTURE_LIST_KEY])
		BULLET_TEXTURES[i++] = loaded_bitmaps[s];
	DAMAGE = data[DATA_JSON_DAMAGE_KEY];
	FIRE_SPEED = data[DATA_JSON_FIRE_SPEED_KEY];
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

#include "GunItem.h"
#include "ResourceLoader.h"
#include "World.h"

std::string GunItem::NAME;
ALLEGRO_BITMAP* GunItem::TEXTURE;
ALLEGRO_BITMAP* GunItem::BULLET_TEXTURE;
float GunItem::DAMAGE;
float GunItem::FIRE_SPEED;
AudioMultiTrackCollection GunItem::AUDIO_TRACKS;

const std::string GunItem::ID = "items.gun";

std::string GunItem::GetID() const
{
	return ID;
}

void GunItem::Fire(World* world, float xpos, float ypos, float rot, Entity* owner)
{
}

GunItem::GunItem() : RangedWeaponItem(NAME)
{}

Item* GunItem::Clone() const
{
	return new GunItem(*this);
}

void GunItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void GunItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	BULLET_TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE0_KEY]);
	DAMAGE = data[DATA_JSON_DAMAGE_KEY];
	FIRE_SPEED = data[DATA_JSON_FIRE_SPEED_KEY];
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

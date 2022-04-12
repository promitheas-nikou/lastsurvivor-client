#include "GunItem.h"
#include "ResourceLoader.h"
#include "World.h"
#include "SimpleBullet.h"

std::string GunItem::NAME;
ALLEGRO_BITMAP* GunItem::TEXTURE;
ALLEGRO_BITMAP* GunItem::BULLET_TEXTURE;
float GunItem::DAMAGE;
float GunItem::FIRE_SPEED;
const std::string GunItem::ID = "items.gun";

std::string GunItem::GetID() const
{
	return ID;
}

void GunItem::Fire(World* world, float xpos, float ypos, float rot, Entity* owner)
{
	SimpleBullet* b = new SimpleBullet(world, DAMAGE, xpos, ypos, FIRE_SPEED * cosf(rot), FIRE_SPEED * sinf(rot), &BULLET_TEXTURE, 1);
	b->SetOwnerEntity(owner);
	world->AddEntity(b);
}

GunItem::GunItem() : RangedWeaponItem(NAME)
{}

Item* GunItem::Clone()const
{
	return nullptr;//new GunItem(*this);
}

void GunItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void GunItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	BULLET_TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE0_KEY]];
	DAMAGE = data[DATA_JSON_DAMAGE_KEY];
	FIRE_SPEED = data[DATA_JSON_FIRE_SPEED_KEY];
}

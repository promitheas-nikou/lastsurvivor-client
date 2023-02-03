#include "SimpleSword.h"
#include "ResourceLoader.h"

std::string SimpleSword::NAME;
ALLEGRO_BITMAP* SimpleSword::TEXTURE;
float SimpleSword::DAMAGE;
float SimpleSword::RANGESQ;
const std::string SimpleSword::ID = "items.wooden_sword";

std::string SimpleSword::GetID() const
{
	return ID;
}

SimpleSword::SimpleSword() : SimpleMeleeWeaponItem(NAME, DAMAGE, RANGESQ)
{}

Item* SimpleSword::Clone() const
{
	return new SimpleSword(*this);
}

void SimpleSword::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
}

void SimpleSword::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	DAMAGE = data[DATA_JSON_DAMAGE_KEY];
	RANGESQ = data[DATA_JSON_RANGESQ_KEY];
}


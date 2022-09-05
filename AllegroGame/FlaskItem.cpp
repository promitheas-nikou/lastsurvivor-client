#include "FlaskItem.h"
#include "ResourceLoader.h"
#include <allegro5/allegro_primitives.h>

std::string FlaskItem::NAME;
std::string FlaskItem::DESCRIPTION;
ALLEGRO_BITMAP* FlaskItem::TEXTURE;
float FlaskItem::HEALTH;
float FlaskItem::HUNGER;
float FlaskItem::WATER;
int FlaskItem::MAX_DURABILITY;
const std::string FlaskItem::ID = "items.flask";

std::string FlaskItem::GetID() const
{
	return ID;
}

int FlaskItem::GetMaxStackSize() const
{
	return 1;
}

FlaskItem::FlaskItem() : SimpleConsumableItem(NAME, DESCRIPTION, HEALTH, HUNGER, WATER), durability{ MAX_DURABILITY }
{}

void FlaskItem::SaveToFile(std::ofstream& file)
{
	Item::SaveToFile(file);
	file.write(reinterpret_cast<const char*>(&durability), sizeof(int));
}

void FlaskItem::LoadAdditionalDataFromFile(std::ifstream& file)
{
	file.read(reinterpret_cast<char*>(&durability), sizeof(int));
}

bool FlaskItem::Consume(float xpos, float ypos, PlayerEntity * player)
{
	if (durability > 0)
	{
		Consumable::Consume(xpos, ypos, player);
		durability--;
	}
	return false;
}

Item* FlaskItem::Clone() const
{
	return new FlaskItem(*this);
}

void FlaskItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_filled_rectangle(x + 10, y + height - 15, x + 10 + (width-20)*(((float)durability)/MAX_DURABILITY), y + height - 10, al_map_rgba(255,0,0,255));
	al_draw_filled_rectangle(x + 10 + (width - 20) * (((float)durability) / MAX_DURABILITY), y + height - 15, x + width - 10, y + height - 10, al_map_rgba(100, 0, 0, 255));
}

void FlaskItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
	MAX_DURABILITY = data[DATA_JSON_DURABILITY_KEY];
}

		
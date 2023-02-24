#include "FlaskItem.h"
#include "ResourceLoader.h"
#include "MathUtils.h"
#include "PlayerEntity.h"
#include "World.h"
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

FlaskItem::FlaskItem() : Item(NAME, DESCRIPTION), durability{ MAX_DURABILITY }
{}

void FlaskItem::SaveToFile(std::ostream& file)
{
	Item::SaveToFile(file);
	file.write(reinterpret_cast<const char*>(&durability), sizeof(int));
}

void FlaskItem::DeserializeFromStream(std::istream& file)
{
	file.read(reinterpret_cast<char*>(&durability), sizeof(int));
}

float FlaskItem::GetHealthBoost() const
{
	return HEALTH;
}

float FlaskItem::GetFoodBoost() const
{
	return HUNGER;
}

float FlaskItem::GetWaterBoost() const
{
	return WATER;
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

bool FlaskItem::Use(float xpos, float ypos, PlayerEntity* player)
{
	int x = util_floor(xpos);
	int y = util_floor(ypos);
	World* w = player->GetContainingWorld();
	Tile* t = w->GetTile(x, y);
	if((t!=nullptr) && (t->IsEmpty()))
		if (w->GetGroundTile(x, y)->GetID() == "gtiles.water")
		{
			durability++;
			if (durability > MAX_DURABILITY)
				durability = MAX_DURABILITY;
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
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	HEALTH = data[DATA_JSON_HEALTH_KEY];
	HUNGER = data[DATA_JSON_HUNGER_KEY];
	WATER = data[DATA_JSON_WATER_KEY];
	MAX_DURABILITY = data[DATA_JSON_DURABILITY_KEY];
}

		
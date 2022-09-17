#include "LogItem.h"
#include "ResourceLoader.h"

std::string LogItem::NAME;
std::string LogItem::DESCRIPTION;
ALLEGRO_BITMAP* LogItem::TEXTURE;
float LogItem::BURN_TIME;
float LogItem::BURN_HEAT;
const std::string LogItem::ID = "items.log";

std::string LogItem::GetID() const
{
	return ID;
}

LogItem::LogItem(): FuelItem(NAME, DESCRIPTION)
{}

float LogItem::GetBurnTime() const
{
	return BURN_TIME;
}

float LogItem::GetBurnHeat() const
{
	return BURN_HEAT;
}

Item* LogItem::Clone() const
{
	return new LogItem(*this);
}

void LogItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void LogItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
	BURN_TIME = data[DATA_JSON_BURN_TIME_KEY];
	BURN_HEAT = data[DATA_JSON_BURN_HEAT_KEY];
}

		
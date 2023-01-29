#include "AnthraciteCoalChunkItem.h"
#include "ResourceLoader.h"


std::string AnthraciteCoalChunkItem::NAME;
std::string AnthraciteCoalChunkItem::DESCRIPTION;
ALLEGRO_BITMAP* AnthraciteCoalChunkItem::TEXTURE;
float AnthraciteCoalChunkItem::BURN_TIME;
float AnthraciteCoalChunkItem::BURN_HEAT;
const std::string AnthraciteCoalChunkItem::ID = "items.anthracite_coal_chunk";

std::string AnthraciteCoalChunkItem::GetID() const
{
    return ID;
}

Item* AnthraciteCoalChunkItem::Clone() const
{
	return new AnthraciteCoalChunkItem(*this);
}

float AnthraciteCoalChunkItem::GetBurnTime() const
{
	return BURN_TIME;
}

float AnthraciteCoalChunkItem::GetBurnHeat() const
{
	return BURN_HEAT;
}

AnthraciteCoalChunkItem::AnthraciteCoalChunkItem() : FuelItem(NAME, DESCRIPTION)
{}

void AnthraciteCoalChunkItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default",30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void AnthraciteCoalChunkItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
	BURN_TIME = data[DATA_JSON_BURN_TIME_KEY];
	BURN_HEAT = data[DATA_JSON_BURN_HEAT_KEY];
}

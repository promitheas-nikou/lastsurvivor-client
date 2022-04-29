#include "QuestGUI.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "ResourceLoader.h"
#include "Graphics.h"

std::vector<bool> questDrawnVisTable;
QuestGUI* __qg;

void QuestGUI::AddQuestDisplayConfiguration(QuestDisplayConfiguration* config)
{
	config->id = displayConfig.size();
	displayConfig.push_back(config);
	questLink[config->quest] = config;
}

void QuestGUI::DrawThisGUI()
{
	__qg = this;
	if (curQuest == nullptr)
	{
		questDrawnVisTable.clear();
		questDrawnVisTable.resize(displayConfig.size()); 
		for (QuestDisplayConfiguration* conf : displayConfig)
		{
			conf->DrawIcon(curx, cury);
		}
		if (curQuestHover != nullptr)
			curQuestHover->DrawHover(curx, cury);
	}
	else
	{
		curQuest->DrawFull();
	}
}

void QuestGUI::ClickRightDown(int xRel, int yRel)
{}

void QuestGUI::ClickLeftDown(int xRel, int yRel)
{
	for (QuestDisplayConfiguration* conf : displayConfig)
	{
		if (conf->Contains(xRel + curx, yRel + cury))
		{
			curQuest = conf;
			return;
		}
	}
}

void QuestGUI::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
	if (event.keycode == ALLEGRO_KEY_ESCAPE)
		curQuest = nullptr;
}

void QuestGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	for (QuestDisplayConfiguration* conf : displayConfig)
	{
		if (conf->Contains(event.x + curx, event.y + cury))
		{
			curQuestHover = conf;
			return;
		}
	}
	curQuestHover = nullptr;
}

QuestGUI::QuestGUI(QuestCollection* col) : curx{ 0 }, cury{ 0 }, curQuest{ nullptr }, questCollection{ col }, curQuestHover{ nullptr }
{
	for (const std::pair<std::string, Quest*>& q : col->quests)
	{
		AddQuestDisplayConfiguration(new QuestDisplayConfiguration(q.second));
	}
}

const ALLEGRO_COLOR COMPLETED_COLOR = al_map_rgba(40, 200, 0, 255);
const ALLEGRO_COLOR NOT_COMPLETED_COLOR = al_map_rgba(80, 80, 80, 255);

void QuestGUI::QuestDisplayConfiguration::DrawIcon(int curx, int cury) const
{
	ALLEGRO_BITMAP* b = quest->GetIcon();
	if (questDrawnVisTable[id])
	{
		al_draw_filled_rectangle(x - curx - 16, y - cury - 16, x + width - curx + 16, y + height - cury + 16, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
		//al_draw_filled_rectangle(x - curx, y - cury, x + width - curx, y + height - cury, al_map_rgba(255, 255, 255, 255));
		al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), x - curx, y - cury, width, height, 0);
		return;
	}
	questDrawnVisTable[id] = true;
	for (Quest::QuestCompletionRequirement q : quest->quest_requirements)
	{
		QuestDisplayConfiguration* c = __qg->questLink[q.targetquest];
		al_draw_line(x - curx + width / 2, y - cury + height / 2, c->x - curx + c->width / 2, c->y - cury + c->height / 2, al_map_rgba(0, 0, 0, 255), 5.f);
		c->DrawIcon(curx, cury);
	}
	al_draw_filled_rectangle(x - curx - 16, y - cury - 16, x + width - curx + 16, y + height - cury + 16, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
	//al_draw_filled_rectangle(x - curx, y - cury, x + width - curx, y + height - cury, al_map_rgba(255,255,255,255));
	al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), x - curx, y - cury, width, height, 0);
}

void QuestGUI::QuestDisplayConfiguration::DrawHover(int curx, int cury) const
{
	ALLEGRO_BITMAP* b = quest->GetIcon();
	al_draw_filled_rectangle(x - curx - 50, y - cury - 50, x - curx + width + 50, y - cury + height + 50, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
	al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), x - curx, y - cury-40, width, height, 0);
	al_draw_filled_rectangle(x - curx - 45, y - cury + height - 40, x - curx + width + 45, y - cury + height + 45, al_map_rgba(255, 255, 255, 255));
	al_draw_text(loaded_fonts["default"][20], al_map_rgba(0, 0, 0, 255), x - curx - 45, y - cury + height - 40, 0, quest->GetName().c_str());
}

static const ALLEGRO_COLOR QUEST_REQ_INCOMPLETE = al_map_rgba(255, 0, 0, 255);
static const ALLEGRO_COLOR QUEST_REQ_COMPLETE = al_map_rgba(0, 255, 0, 255);

void QuestGUI::QuestDisplayConfiguration::DrawFull() const
{
	ALLEGRO_BITMAP* b = quest->GetIcon();
	al_draw_filled_rectangle(32, 32, SCREEN_WIDTH-32, 320, al_map_rgba(255,255,255,255));
	al_draw_filled_rectangle(SCREEN_WIDTH - 320, 32, SCREEN_WIDTH - 32, 320, al_map_rgba(200,200,200,255));
	al_draw_filled_rectangle(SCREEN_WIDTH - 304, 48, SCREEN_WIDTH - 48, 304, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
	al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), 48, 48, 256, 256, 0);
	al_draw_text(loaded_fonts["default"][80], al_map_rgba(0, 0, 0, 255), 320, 144, 0, quest->GetName().c_str());
	al_draw_filled_rectangle(32, 360, SCREEN_WIDTH - 32, SCREEN_HEIGHT - 32, al_map_rgba(255, 255, 255, 255));
	al_draw_textf(loaded_fonts["default"][40], al_map_rgba(0, 0, 0, 255), 32, 360, 0, "Requirements:");
	int Y = 360;

	al_draw_textf(loaded_fonts["default"][40], al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Quest Requirements:");
	Y += 20;
	for (Quest::QuestCompletionRequirement r : quest->quest_requirements)
		al_draw_textf(loaded_fonts["default"][40], r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Complete Quest \"%s\" (%s)", r.targetquest->GetName().c_str(), r.Check() ? "COMPLETE" : "INCOMPLETE");

	al_draw_textf(loaded_fonts["default"][40], al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Tile Mine Requirements:");
	Y += 20;
	for (Quest::TileMineRequirement r : quest->tile_requirements)
		al_draw_textf(loaded_fonts["default"][40], r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Mine Tile \"%s\" (%d/%d)", prototype_tiles[r.tileid]->GetName().c_str(), r.progress, r.count);

	al_draw_textf(loaded_fonts["default"][40], al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Ground Tile Mine Requirements:");
	Y += 20;
	for (Quest::GroundTileMineRequirement r : quest->gtile_requirements)
		al_draw_textf(loaded_fonts["default"][40], r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Mine Ground Tile \"%s\" (%d/%d)", prototype_gtiles[r.gtileid]->GetName().c_str(), r.progress, r.count);

	al_draw_textf(loaded_fonts["default"][40], al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Entity Kill Requirements:");
	Y += 20;
	for (Quest::EntityKillRequirement r : quest->kill_requirements)
		al_draw_textf(loaded_fonts["default"][40], r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Kill Entity \"%s\" (%d/%d)", prototype_entities[r.entityid]->GetName().c_str(), r.progress, r.count);
}

bool QuestGUI::QuestDisplayConfiguration::Contains(int xp, int yp) const
{
	return (xp >= x) && (xp <= x + width) && (yp >= y) && (yp <= y + height);
}

QuestGUI::QuestDisplayConfiguration::QuestDisplayConfiguration(Quest* q) : x{ q->x }, y{ q->y }, width{ 128 }, height{ 128 }, quest{ q }
{
}

#include "QuestGUI.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "ResourceLoader.h"
#include "Graphics.h"
#include <set>

std::set<Quest*> questDrawnVisTable;
QuestGUI* __qg;

void QuestGUI::PreDrawThisGUI()
{
	al_set_system_mouse_cursor(main_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(100, 100, 100, 150));
	__qg = this;
	if (curQuest == nullptr)
	{
		questDrawnVisTable.clear();
		for (int i=0;i<questCollection->GetQuestCount();i++)
		{
			if (questDrawnVisTable.count(questCollection->GetQuest(i)))
				continue;
			questDrawnVisTable.insert(questCollection->GetQuest(i));
			QuestDrawIcon(questCollection->GetQuest(i), curx, cury);
		}
		if (curQuestHover != nullptr)
			QuestDrawHover(curQuestHover, curx, cury);
	}
	else
	{
		QuestDrawFull(curQuest);
	}
}

void QuestGUI::PostDrawThisGUI()
{

}

bool QuestGUI::ClickRightDown(int xRel, int yRel)
{
	return true;
}

bool QuestGUI::ClickLeftDown(int xRel, int yRel)
{
	for (int i = 0; i < questCollection->GetQuestCount(); i++)
	{
		if (QuestContains(questCollection->GetQuest(i), xRel + curx, yRel + cury))
		{
			curQuest = questCollection->GetQuest(i);
			return true;
		}
	}
	return true;
}

bool QuestGUI::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
	if ((curQuest!=nullptr)&&(event.keycode == ALLEGRO_KEY_ESCAPE))
	{
		curQuest = nullptr;
		return true;
	}
	return false;
}

extern int mousex;
extern int mousey;

bool QuestGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	for (int i = 0; i < questCollection->GetQuestCount(); i++)
	{
		if (QuestContains(questCollection->GetQuest(i), event.x + curx, event.y + cury))
		{
			curQuestHover = questCollection->GetQuest(i);
			return true;
		}
	}
	ALLEGRO_MOUSE_STATE s;
	al_get_mouse_state(&s);
	curQuestHover = nullptr;

	if (al_mouse_button_down(&s, 1))
	{
		curx -= event.dx;
		cury -= event.dy;
	}
	return true;
}

QuestGUI::QuestGUI(QuestCollection* col) : curx{ 0 }, cury{ 0 }, curQuest{ nullptr }, questCollection{ col }, curQuestHover{ nullptr }
{}

const ALLEGRO_COLOR COMPLETED_COLOR = al_map_rgba(40, 200, 0, 255);
const ALLEGRO_COLOR NOT_COMPLETED_COLOR = al_map_rgba(80, 80, 80, 255);

void QuestGUI::QuestDrawIcon(Quest* quest, int curx, int cury) const
{
	ALLEGRO_BITMAP* b = quest->GetIcon();
	if (questDrawnVisTable.count(quest))
	{
		al_draw_filled_rectangle(quest->GetXpos() - curx - 16, quest->GetYpos() - cury - 16, quest->GetXpos() + WIDTH - curx + 16, quest->GetYpos() + HEIGHT - cury + 16, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
		//al_draw_filled_rectangle(x - curx, y - cury, x + width - curx, y + height - cury, al_map_rgba(255, 255, 255, 255));
		al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), quest->GetXpos() - curx, quest->GetYpos() - cury, WIDTH, HEIGHT, 0);
		return;
	}
	questDrawnVisTable.insert(quest);
	for (Quest::QuestCompletionRequirement q : quest->quest_requirements)
	{
		Quest* t = q.targetquest;
		al_draw_line(quest->GetXpos() - curx + WIDTH / 2, quest->GetYpos() - cury + HEIGHT / 2, t->GetXpos() - curx + WIDTH / 2, t->GetYpos() - cury + HEIGHT / 2, al_map_rgba(0, 0, 0, 255), 5.f);
		QuestDrawIcon(t, curx, cury);
	}
	al_draw_filled_rectangle(quest->GetXpos() - curx - 16, quest->GetYpos() - cury - 16, quest->GetXpos() + WIDTH - curx + 16, quest->GetYpos() + HEIGHT - cury + 16, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
	//al_draw_filled_rectangle(x - curx, y - cury, x + width - curx, y + height - cury, al_map_rgba(255,255,255,255));
	al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), quest->GetXpos() - curx, quest->GetYpos() - cury, WIDTH, HEIGHT, 0);
}

void QuestGUI::QuestDrawHover(Quest* quest, int curx, int cury) const
{
	ALLEGRO_BITMAP* b = quest->GetIcon();
	al_draw_filled_rectangle(quest->GetXpos() - curx - 50, quest->GetYpos() - cury - 50, quest->GetXpos() - curx + WIDTH + 50, quest->GetYpos() - cury + HEIGHT + 50, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
	al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), quest->GetXpos() - curx, quest->GetYpos() - cury-40, WIDTH, HEIGHT, 0);
	al_draw_filled_rectangle(quest->GetXpos() - curx - 45, quest->GetYpos() - cury + HEIGHT - 40, quest->GetXpos() - curx + WIDTH + 45, quest->GetYpos() - cury + HEIGHT + 45, al_map_rgba(255, 255, 255, 255));
	al_draw_text(game_GetFont("default", 20), al_map_rgba(0, 0, 0, 255), quest->GetXpos() - curx - 45, quest->GetYpos() - cury + HEIGHT - 40, 0, quest->GetName().c_str());
}

static const ALLEGRO_COLOR QUEST_REQ_INCOMPLETE = al_map_rgba(255, 0, 0, 255);
static const ALLEGRO_COLOR QUEST_REQ_COMPLETE = al_map_rgba(0, 255, 0, 255);

void QuestGUI::QuestDrawFull(Quest* quest) const
{
	ALLEGRO_BITMAP* b = quest->GetIcon();
	al_draw_filled_rectangle(32, 32, SCREEN_WIDTH-32, 320, al_map_rgba(255,255,255,255));
	al_draw_filled_rectangle(SCREEN_WIDTH - 320, 32, SCREEN_WIDTH - 32, 320, al_map_rgba(200,200,200,255));
	al_draw_filled_rectangle(SCREEN_WIDTH - 304, 48, SCREEN_WIDTH - 48, 304, quest->IsCompleted() ? COMPLETED_COLOR : NOT_COMPLETED_COLOR);
	al_draw_scaled_bitmap(b, 0, 0, al_get_bitmap_width(b), al_get_bitmap_height(b), 48, 48, 256, 256, 0);
	al_draw_text(game_GetFont("default", 80), al_map_rgba(0, 0, 0, 255), 320, 144, 0, quest->GetName().c_str());
	al_draw_filled_rectangle(32, 360, SCREEN_WIDTH - 32, SCREEN_HEIGHT - 32, al_map_rgba(255, 255, 255, 255));
	al_draw_textf(game_GetFont("default", 40), al_map_rgba(0, 0, 0, 255), 32, 360, 0, "Requirements:");
	int Y = 360;

	al_draw_textf(game_GetFont("default", 40), al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Quest Requirements:");
	Y += 20;
	for (Quest::QuestCompletionRequirement r : quest->quest_requirements)
		al_draw_textf(game_GetFont("default", 40), r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Complete Quest \"%s\" (%s)", r.targetquest->GetName().c_str(), r.Check() ? "COMPLETE" : "INCOMPLETE");

	al_draw_textf(game_GetFont("default", 40), al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Tile Mine Requirements:");
	Y += 20;
	for (Quest::TileMineRequirement r : quest->tile_requirements)
		al_draw_textf(game_GetFont("default", 40), r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Mine Tile \"%s\" (%d/%d)", prototype_tiles[r.tileid]->GetName().c_str(), r.progress, r.count);

	al_draw_textf(game_GetFont("default", 40), al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Ground Tile Mine Requirements:");
	Y += 20;
	for (Quest::GroundTileMineRequirement r : quest->gtile_requirements)
		al_draw_textf(game_GetFont("default", 40), r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Mine Ground Tile \"%s\" (%d/%d)", prototype_gtiles[r.gtileid]->GetName().c_str(), r.progress, r.count);

	al_draw_textf(game_GetFont("default", 40), al_map_rgba(0, 0, 0, 255), 48, Y += 60, 0, "Entity Kill Requirements:");
	Y += 20;
	for (Quest::EntityKillRequirement r : quest->kill_requirements)
		al_draw_textf(game_GetFont("default", 40), r.Check() ? QUEST_REQ_COMPLETE : QUEST_REQ_INCOMPLETE, 64, Y += 40, 0, "Kill Entity \"%s\" (%d/%d)", prototype_entities[r.entityid]->GetName().c_str(), r.progress, r.count);
}

bool QuestGUI::QuestContains(Quest* q, int xp, int yp) const
{
	return (xp >= q->GetXpos()) && (xp <= q->GetXpos() + WIDTH) && (yp >= q->GetYpos()) && (yp <= q->GetYpos() + HEIGHT);
}

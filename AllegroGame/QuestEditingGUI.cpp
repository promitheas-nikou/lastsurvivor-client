#include "QuestEditingGUI.h"
#include "Config.h"
#include "ResourceLoader.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "Graphics.h"
#include "SimpleTextButtonUIComponent.h"
#include <algorithm>
#include "PlayerEntity.h"

void QuestEditingGUI::DrawQuestIcon(const Quest* quest, int x, int y, int tw, int th, int rw, int rh)
{
	al_draw_filled_rectangle(x, y, x + tw, y + th, gameconfig::SOLID_BACKGROUND_COLOR_0);
	ALLEGRO_BITMAP* bmp = quest->GetIcon();
	al_draw_scaled_bitmap(quest->GetIcon(), 0, 0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), x + 5, y + 5, rw-10, rh-10, 0);
	al_draw_textf(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_NORMAL, x + rw, y + rh / 2 - 15, 0, "\"%s\"", quest->GetName().c_str());
}

void QuestEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	for (int i = 0; i < std::min(pageHeight, questCollection->GetQuestCount() - scroll); i++)
		DrawQuestIcon(questCollection->GetQuest(i + scroll), 148, 148 + i * 148, SCREEN_WIDTH - 296, 138, 138, 138);
	//al_draw_filled_rectangle(148, SCREEN_HEIGHT-276, SCREEN_WIDTH - 148, SCREEN_HEIGHT-148, gameconfig::SOLID_BACKGROUND_COLOR_0);
	//al_draw_text(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_NORMAL, 158, SCREEN_HEIGHT - 276 + 49, 0, "CREATE NEW QUEST");
}

void QuestEditingGUI::PostDrawThisGUI()
{

}

bool QuestEditingGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll > questCollection->GetQuestCount() - pageHeight)
		scroll = std::max(0, questCollection->GetQuestCount() - pageHeight);
	return true;
}

bool QuestEditingGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= (128 + 20)) && (event.y <= SCREEN_HEIGHT - 128))
	{
		int ind = ((event.y - (128 + 20)) / (128+20)) + scroll;
		if (ind < questCollection->GetQuestCount())
		{
			activeSubGUI = questEditingGUI;
			questEditingGUI->SetQuestIndex(ind);
		}
	}
	return true;
}

void QuestEditingGUI::SetCurrentPlayer(PlayerEntity* p)
{
	player = p;
}

void QuestEditingGUI::SetQuestCollection(QuestCollection* col)
{
	questCollection = col;
}

QuestCollection* QuestEditingGUI::GetQuestCollection() const
{
	return questCollection;
}

QuestEditingGUI::QuestEditingGUI(PlayerEntity* p, int pageHeight) : player{ p }, pageHeight{ pageHeight }
{
	questCreationGUI = new NewQuestCreationGUI(this);
	questEditingGUI = new ExistingQuestEditingGUI(this);
	UIcomponents.push_back(new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [this]() {
		activeSubGUI = questCreationGUI;
	}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "CREATE NEW QUEST"));
}

void QuestEditingGUI::NewQuestCreationGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
}

bool QuestEditingGUI::NewQuestCreationGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	return true;
}


extern std::unordered_map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps;

QuestEditingGUI::NewQuestCreationGUI::NewQuestCreationGUI(QuestEditingGUI* par) : parent{ par }
{
	UIcomponents.push_back(idTextInput = new SimpleTextInputUIComponent(148, 296, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest ID: [", "quests.", "]", 0));
	UIcomponents.push_back(nameTextInput = new SimpleTextInputUIComponent(148, 296+(gameconfig::GUI_DEFAULT_LINE_HEIGHT+20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest Name: [", "", "]", 0));
	UIcomponents.push_back(iconIDTextInput = new SimpleTextInputUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20)*2, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest Icon ID: [", "tex.", "]", 0));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296) / 2 - 32, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		if (loaded_bitmaps.count(iconIDTextInput->GetTextBuffer()))
		{
			parent->GetQuestCollection()->AddQuest(Quest::MakeNewQuest(idTextInput->GetTextBuffer(), nameTextInput->GetTextBuffer(), iconIDTextInput->GetTextBuffer(), 100, 100, false, true));
			parent->SetActiveSubGUI(nullptr);
		}
		else
			iconIDTextInput->SetAlert("INVALID BITMAP ID!", gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "DONE"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 32, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296) / 2 - 32, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
}

void QuestEditingGUI::ExistingQuestEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
}

QuestEditingGUI::ExistingQuestEditingGUI::ExistingQuestEditingGUI(QuestEditingGUI* par) : parent{ par }
{
	requiremenentEditingGUI = new QuestRequirementEditingGUI(this);
	UIcomponents.push_back(idTextInput = new SimpleTextInputUIComponent(148, 296, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest ID: [", "", "]", 0));
	UIcomponents.push_back(nameTextInput = new SimpleTextInputUIComponent(148, 296+(gameconfig::GUI_DEFAULT_LINE_HEIGHT+20) * 1, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest NameID: [", "", "]", 0));
	UIcomponents.push_back(iconIDTextInput = new SimpleTextInputUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 2, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest Icon ID: [", "", "]", 0));
	UIcomponents.push_back(completedToggleButton = new SimpleToggleTextButtonUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 3, SCREEN_WIDTH / 2 - 168, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Is Completed? :", false));
	UIcomponents.push_back(unlockedToggleButton = new SimpleToggleTextButtonUIComponent(SCREEN_WIDTH/2 + 20, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 3, SCREEN_WIDTH / 2 - 168, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Is Unlocked? :", true));
	UIcomponents.push_back(xNumInput = new SimpleNumberInputUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 4, SCREEN_WIDTH / 2 - 168, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest X: [", "", "]", ALLEGRO_ALIGN_LEFT));
	UIcomponents.push_back(yNumInput = new SimpleNumberInputUIComponent(SCREEN_WIDTH / 2 + 20, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 4, SCREEN_WIDTH / 2 - 168, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest Y: [", "", "]", ALLEGRO_ALIGN_LEFT));
	UIcomponents.push_back(editQuestRequirementsButton = new SimpleTextButtonUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 5, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		requiremenentEditingGUI->SetQuest(parent->questCollection->GetQuest(questIndex));
		activeSubGUI = requiremenentEditingGUI;
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Edit Quest Requirements"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296) / 2 - 32, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		if (loaded_bitmaps.count(iconIDTextInput->GetTextBuffer()))
		{
			QuestCollection* qc = parent->GetQuestCollection();
			Quest* q = qc->GetQuest(questIndex);
			q->Modify(nameTextInput->GetTextBuffer(), iconIDTextInput->GetTextBuffer(), xNumInput->GetInputNumber(), yNumInput->GetInputNumber(), completedToggleButton->GetIsToggledOn(), unlockedToggleButton->GetIsToggledOn());
			qc->ReIDQuest(q->GetID(), idTextInput->GetTextBuffer());
			parent->SetActiveSubGUI(nullptr);
		}
		else
			iconIDTextInput->SetAlert("INVALID BITMAP ID!", gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "DONE"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 32, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296) / 2 - 32, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
}

void QuestEditingGUI::ExistingQuestEditingGUI::SetQuestIndex(int i)
{
	questIndex = i;
	Quest* q = parent->questCollection->GetQuest(i);
	idTextInput->SetTextBuffer(q->GetID());
	nameTextInput->SetTextBuffer(q->GetName());
	iconIDTextInput->SetTextBuffer(q->GetIconID());
	xNumInput->SetTextBuffer(std::format("{}", q->GetXpos()));
	yNumInput->SetTextBuffer(std::format("{}", q->GetYpos()));
	completedToggleButton->SetIsToggledOn(q->IsCompleted());
	unlockedToggleButton->SetIsToggledOn(q->IsUnlocked());
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestRequirementEditingGUI(ExistingQuestEditingGUI* par) : parent{ par }, quest{ nullptr }
{
	tileRequirementEditingGUI = new TileQuestRequirementEditingGUI(this);
	gtileRequirementEditingGUI = new GroundTileQuestRequirementEditingGUI(this);
	killRequirementEditingGUI = new EntityKillQuestRequirementEditingGUI(this);
	questRequirementEditingGUI = new QuestCompletionQuestRequirementEditingGUI(this);
	UIcomponents.push_back(tileRequirementButton = new SimpleTextButtonUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 0, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		activeSubGUI = tileRequirementEditingGUI;
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Edit Tile Mine Requirements"));
	UIcomponents.push_back(gtileRequirementButton = new SimpleTextButtonUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 1, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		activeSubGUI = gtileRequirementEditingGUI;
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Edit Ground Tile Mine Requirements"));
	UIcomponents.push_back(killRequirementButton = new SimpleTextButtonUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 2, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		activeSubGUI = killRequirementEditingGUI;
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Entity Kill Requirements"));
	UIcomponents.push_back(questRequirementButton = new SimpleTextButtonUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20) * 3, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		activeSubGUI = questRequirementEditingGUI;
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest Completion Requirements"));
	UIcomponents.push_back(backButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "BACK"));
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::SetQuest(Quest* q)
{
	quest = q;
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::DrawRequirementIcon(const Quest::TileMineRequirement& req, int x, int y, int lw, int lh)
{
	al_draw_filled_rectangle(x, y, x + lw, y + lh, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_textf(game_GetFont("default", 30),gameconfig::SOLID_TEXT_COLOR_NORMAL, x+10, y+lh/2-15, 0, "MINE %d \"%s\" (#%s) [CLICK TO DELETE]", req.count, prototype_tiles.count(req.tileid)?prototype_tiles[req.tileid]->GetName().c_str():"<INVALID>", req.tileid.c_str());
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	for (int i = 0; i < std::min(pageHeight, parent->quest->GetTileMineRequirementCount() - scroll); i++)
		DrawRequirementIcon(parent->quest->GetTileMineRequirement(i+scroll), 148, 296 + i * (gameconfig::GUI_DEFAULT_LINE_HEIGHT+20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT);
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll > parent->quest->GetTileMineRequirementCount() - pageHeight)
		scroll = std::max(0, parent->quest->GetTileMineRequirementCount() - pageHeight);
	return true;
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= (128 + 20)) && (event.y <= SCREEN_HEIGHT - 128 - 148))
	{
		int ind = ((event.y - 296) / (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20)) + scroll;
		if (ind < parent->quest->GetTileMineRequirementCount())
		{
			parent->quest->EraseTileMineRequirement(ind);
		}
	}
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::TileQuestRequirementEditingGUI(QuestRequirementEditingGUI * par, int pageHeight) : parent{ par }, pageHeight{ pageHeight }, scroll{ 0 }
{
	creationGUI = new NewTileQuestRequirementCreationGUI(this);
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(newButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		SetActiveSubGUI(creationGUI);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "NEW"));
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::NewTileQuestRequirementCreationGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::TileQuestRequirementEditingGUI::NewTileQuestRequirementCreationGUI::NewTileQuestRequirementCreationGUI(TileQuestRequirementEditingGUI* par) : parent{ par }
{
	UIcomponents.push_back(tileIDTextInput = new SimpleTextInputUIComponent(148, 296, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Tile ID: [", "tiles.", "]", 0));
	UIcomponents.push_back(tileCountNumberInput = new SimpleNumberInputUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Target Count: [", "0", "]", 0));
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		if (!prototype_tiles.count(tileIDTextInput->GetTextBuffer()))
		{
			tileIDTextInput->SetAlert("INVALID TILE ID", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		if (tileCountNumberInput->GetInputNumber()<=0)
		{
			tileCountNumberInput->SetAlert("TARGET COUNT MUST BE POSITIVE INTEGER", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		parent->parent->quest->AddTileMineRequirement(tileIDTextInput->GetTextBuffer(), tileCountNumberInput->GetInputNumber());
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "DONE"));
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::DrawRequirementIcon(const Quest::GroundTileMineRequirement& req, int x, int y, int lw, int lh)
{
	al_draw_filled_rectangle(x, y, x + lw, y + lh, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_textf(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_NORMAL, x + 10, y + lh / 2 - 15, 0, "MINE %d \"%s\" (#%s) [CLICK TO DELETE]", req.count, prototype_gtiles.count(req.gtileid) ? prototype_gtiles[req.gtileid]->GetName().c_str() : "<INVALID>", req.gtileid.c_str());
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	for (int i = 0; i < std::min(pageHeight, parent->quest->GetGroundTileMineRequirementCount() - scroll); i++)
		DrawRequirementIcon(parent->quest->GetGroundTileMineRequirement(i + scroll), 148, 296 + i * (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT);
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll > parent->quest->GetGroundTileMineRequirementCount() - pageHeight)
		scroll = std::max(0, parent->quest->GetTileMineRequirementCount() - pageHeight);
	return true;
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= (128 + 20)) && (event.y <= SCREEN_HEIGHT - 128 - 148))
	{
		int ind = ((event.y - 296) / (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20)) + scroll;
		if (ind < parent->quest->GetTileMineRequirementCount())
		{
			parent->quest->EraseTileMineRequirement(ind);
		}
	}
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight) : parent{ par }, pageHeight{ pageHeight }, scroll{ 0 }
{
	creationGUI = new NewGroundTileQuestRequirementCreationGUI(this);
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(newButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		SetActiveSubGUI(creationGUI);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "NEW"));
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::NewGroundTileQuestRequirementCreationGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::GroundTileQuestRequirementEditingGUI::NewGroundTileQuestRequirementCreationGUI::NewGroundTileQuestRequirementCreationGUI(GroundTileQuestRequirementEditingGUI* par) : parent{ par }
{
	UIcomponents.push_back(gtileIDTextInput = new SimpleTextInputUIComponent(148, 296, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Ground Tile ID: [", "gtiles.", "]", 0));
	UIcomponents.push_back(gtileCountNumberInput = new SimpleNumberInputUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Target Count: [", "0", "]", 0));
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		if (!prototype_gtiles.count(gtileIDTextInput->GetTextBuffer()))
		{
			gtileIDTextInput->SetAlert("INVALID GTILE ID", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		if (gtileCountNumberInput->GetInputNumber() <= 0)
		{
			gtileCountNumberInput->SetAlert("TARGET COUNT MUST BE POSITIVE INTEGER", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		parent->parent->quest->AddGroundTileMineRequirement(gtileIDTextInput->GetTextBuffer(), gtileCountNumberInput->GetInputNumber());
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "DONE"));
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::DrawRequirementIcon(const Quest::EntityKillRequirement& req, int x, int y, int lw, int lh)
{
	al_draw_filled_rectangle(x, y, x + lw, y + lh, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_textf(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_NORMAL, x + 10, y + lh / 2 - 15, 0, "KILL %d \"%s\" (#%s) [CLICK TO DELETE]", req.count, prototype_tiles.count(req.entityid) ? prototype_gtiles[req.entityid]->GetName().c_str() : "<INVALID>", req.entityid.c_str());
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	for (int i = 0; i < std::min(pageHeight, parent->quest->GetEntityKillRequirementCount() - scroll); i++)
		DrawRequirementIcon(parent->quest->GetEntityKillRequirement(i + scroll), 148, 296 + i * (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT);
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll > parent->quest->GetEntityKillRequirementCount() - pageHeight)
		scroll = std::max(0, parent->quest->GetEntityKillRequirementCount() - pageHeight);
	return true;
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= (128 + 20)) && (event.y <= SCREEN_HEIGHT - 128 - 148))
	{
		int ind = ((event.y - 296) / (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20)) + scroll;
		if (ind < parent->quest->GetEntityKillRequirementCount())
		{
			parent->quest->EraseEntityKillRequirement(ind);
		}
	}
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight) : parent{ par }, pageHeight{ pageHeight }, scroll{ 0 }
{
	creationGUI = new NewEntityKillQuestRequirementCreationGUI(this);
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(newButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		SetActiveSubGUI(creationGUI);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "NEW"));
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::NewEntityKillQuestRequirementCreationGUI::NewEntityKillQuestRequirementCreationGUI(EntityKillQuestRequirementEditingGUI* par) : parent{ par }
{
	UIcomponents.push_back(entityIDTextInput = new SimpleTextInputUIComponent(148, 296, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Entity ID: [", "entities.", "]", 0));
	UIcomponents.push_back(killCountNumberInput = new SimpleNumberInputUIComponent(148, 296 + (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Target Count: [", "0", "]", 0));
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		if (!prototype_entities.count(entityIDTextInput->GetTextBuffer()))
		{
			entityIDTextInput->SetAlert("INVALID ENTITY ID", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		if (killCountNumberInput->GetInputNumber() <= 0)
		{
			killCountNumberInput->SetAlert("TARGET COUNT MUST BE POSITIVE INTEGER", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		parent->parent->quest->AddEntityKillRequirement(entityIDTextInput->GetTextBuffer(), killCountNumberInput->GetInputNumber());
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "DONE"));
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::EntityKillQuestRequirementEditingGUI::NewEntityKillQuestRequirementCreationGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	return true;
}


//==========================================================================

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::DrawRequirementIcon(const Quest::QuestCompletionRequirement& req, int x, int y, int lw, int lh)
{
	al_draw_filled_rectangle(x, y, x + lw, y + lh, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_textf(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_NORMAL, x + 10, y + lh / 2 - 15, 0, "COMPLETE QUEST \"%s\" (#%s) [CLICK TO DELETE]", req.targetquest->GetName().c_str(), req.id.c_str());
}

void QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	for (int i = 0; i < std::min(pageHeight, parent->quest->GetQuestCompletionRequirementCount() - scroll); i++)
		DrawRequirementIcon(parent->quest->GetQuestCompletionRequirement(i + scroll), 148, 296 + i * (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20), SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT);
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll > parent->quest->GetEntityKillRequirementCount() - pageHeight)
		scroll = std::max(0, parent->quest->GetEntityKillRequirementCount() - pageHeight);
	return true;
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= (128 + 20)) && (event.y <= SCREEN_HEIGHT - 128 - 148))
	{
		int ind = ((event.y - 296) / (gameconfig::GUI_DEFAULT_LINE_HEIGHT + 20)) + scroll;
		if (ind < parent->quest->GetQuestCompletionRequirementCount())
		{
			parent->quest->GetQuestCompletionRequirement(ind);
		}
	}
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight) : parent{ par }, pageHeight{ pageHeight }, scroll{ 0 }
{
	creationGUI = new NewQuestCompletionQuestRequirementCreationGUI(this);
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(newButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		SetActiveSubGUI(creationGUI);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "NEW"));
}

bool QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::NewQuestCompletionQuestRequirementCreationGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	return true;
}

QuestEditingGUI::ExistingQuestEditingGUI::QuestRequirementEditingGUI::QuestCompletionQuestRequirementEditingGUI::NewQuestCompletionQuestRequirementCreationGUI::NewQuestCompletionQuestRequirementCreationGUI(QuestCompletionQuestRequirementEditingGUI* par) : parent{ par }
{
	UIcomponents.push_back(questIDTextInput = new SimpleTextInputUIComponent(148, 296, SCREEN_WIDTH - 296, gameconfig::GUI_DEFAULT_LINE_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_NORMAL, "Quest ID: [", "quests.", "]", 0));
	UIcomponents.push_back(cancelButton = new SimpleTextButtonUIComponent(148, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR, "CANCEL"));
	UIcomponents.push_back(doneButton = new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 16, SCREEN_HEIGHT - 148 - gameconfig::GUI_DEFAULT_LINE_HEIGHT, (SCREEN_WIDTH - 296 - 32) / 2, gameconfig::GUI_DEFAULT_LINE_HEIGHT, [&]() {
		if (!parent->parent->parent->parent->questCollection->GetQuest(questIDTextInput->GetTextBuffer()))
		{
			questIDTextInput->SetAlert("INVALID QUEST ID", gameconfig::SOLID_TEXT_COLOR_ERROR, gameconfig::SOLID_BACKGROUND_COLOR_0);
			return;
		}
		parent->parent->quest->AddQuestCompletionRequirement(questIDTextInput->GetTextBuffer());
		parent->parent->quest->Resolve();
		parent->SetActiveSubGUI(nullptr);
		}, gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_OK, "DONE"));
}


#include "PlayerEntity.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "ResourceLoader.h"
#include "SimpleButtonUIComponent.h"
#include "SimpleItemInventory.h"
#include "SimpleInventoryGUI.h"
#include "Graphics.h"
#include "World.h"
#include "RecipeListGUI.h"
#include "SimpleRecipeListGUI.h"
#include "LuaInterface.h"
#include "SimpleSword.h"
#include "GunItem.h"
#include "Consumable.h"
#include "BerryItem.h"
#include "Graphics.h"
#include <functional>
#include "DebugInfo.h"
#include "MathUtils.h"
#include <allegro5/allegro_native_dialog.h>
#include <algorithm>
#include "AllegroGame.h"
#include "SimpleTextButtonUIComponent.h"
#include "Config.h"
#include "DrawUtils.h"
#define _USE_MATH_DEFINES
#include <math.h>

ALLEGRO_BITMAP* PlayerEntity::TEXTURE;

std::string PlayerEntity::NAME;
float PlayerEntity::RANGESQ;
float PlayerEntity::MAX_HUNGER;
float PlayerEntity::HUNGER_LOSS_PER_TICK;
float PlayerEntity::HEALTH_LOSS_FROM_HUNGER_PER_TICK;
float PlayerEntity::MAX_WATER;
float PlayerEntity::WATER_LOSS_PER_TICK;
float PlayerEntity::HEALTH_LOSS_FROM_WATER_PER_TICK;
AudioMultiTrackCollection PlayerEntity::AUDIO_TRACKS;
ALLEGRO_BITMAP* HEALTH_ICON;
ALLEGRO_BITMAP* HUNGER_ICON;
ALLEGRO_BITMAP* WATER_ICON;

int a, b, c;

#define GET_MOUSE_XPOS(E) (E / 128.f + GetXpos() - (SCREEN_WIDTH / 256.f))
#define GET_MOUSE_YPOS(E) (E / 128.f + GetYpos() - (SCREEN_HEIGHT / 256.f))

void PlayerEntity::AddResult(const ItemBundle* b)
{
	if (b == nullptr)
		return;
	for (int i = 0; i < b->GetSize(); i++)
		GiveConstItem(b->GetItem(i));
}

Item* PlayerEntity::SwapStashedItem(Item* newItem)
{
	Item* oldItem = GetStashedItem();
	SetStashedItem(newItem);
	return oldItem;
}

Item*& PlayerEntity::GetStashedItem()
{
	return stashedItem;
}

void PlayerEntity::SetStashedItem(Item* newItem)
{
	stashedItem = newItem;
}

void PlayerEntity::LoadAdditionalDataFromFile(std::ifstream& file)
{
	Entity::LoadAdditionalDataFromFile(file);
	file.read(reinterpret_cast<char*>(&hunger), sizeof(float));
	file.read(reinterpret_cast<char*>(&water), sizeof(float));

	pickaxeTool = Item::LoadFromFile(file);
	axeTool = Item::LoadFromFile(file);
	shovelTool = Item::LoadFromFile(file);
	pumpTool = Item::LoadFromFile(file);
	meleeWeapon = Item::LoadFromFile(file);
	rangedWeapon = Item::LoadFromFile(file);

	placeablesInventory->OverrideFromFile(file);
	consumablesInventory->OverrideFromFile(file);
	placeablesInventory->OverrideFromFile(file);

	inventory->OverrideFromFile(file);
}

void PlayerEntity::WriteAdditionalDataToFile(std::ofstream& file)
{
	Entity::WriteAdditionalDataToFile(file);
	file.write(reinterpret_cast<char*>(&hunger), sizeof(float));
	file.write(reinterpret_cast<char*>(&water), sizeof(float));
	Item::SaveToFile(pickaxeTool, file);
	Item::SaveToFile(axeTool, file);
	Item::SaveToFile(shovelTool, file);
	Item::SaveToFile(pumpTool, file);
	Item::SaveToFile(meleeWeapon, file);
	Item::SaveToFile(rangedWeapon, file);

	placeablesInventory->SaveToFile(file);
	consumablesInventory->SaveToFile(file);
	usablesInventory->SaveToFile(file);

	inventory->SaveToFile(file);
}

Entity* PlayerEntity::Clone(World* world, float x, float y) const
{
	return new PlayerEntity(world, x, y);
}

void PlayerEntity::EntityKilledRemote(Entity* e)
{
	if (GetContainingWorld()->GetQuestCollection() != nullptr)
		GetContainingWorld()->GetQuestCollection()->EntityKilled(e);
}

const std::string PlayerEntity::ID = "entities.player";

bool PlayerEntity::Mine()
{
	if (GroundTileMiner::Mine())
	{
		if(GetContainingWorld()->GetQuestCollection()!=nullptr)
			GetContainingWorld()->GetQuestCollection()->MinedGroundTile(GroundTileMiner::GetTarget(), GroundTileMiner::GetTool());
		return true;
	}
	return false;
}

std::string PlayerEntity::GetID() const
{
	return ID;
}

void PlayerEntity::LogToConsole(std::string txt) const
{
	history.push_front(std::make_pair(al_map_rgba(110, 110, 110, 255), txt));
}

constexpr int SELECTED_HOTBAR_SLOT_RECT_WIDTH = 6;

extern int mousex;
extern int mousey;

void PlayerEntity::PreDrawThisGUI()
{
	al_lock_mutex(worldMutex);
	loaded_shaders["world"]->Use();
	containingWorld->Draw();
	loaded_shaders["gui"]->Use();
	ALLEGRO_TRANSFORM gui_transform;
	ALLEGRO_TRANSFORM backup_transorm;
	al_copy_transform(&gui_transform, al_get_current_transform());
	al_copy_transform(&backup_transorm, al_get_current_transform());
	//al_scale_transform(&gui_transform, .5, .5);
	al_use_transform(&gui_transform);
	//ALLEGRO_MOUSE_STATE mouseState;
	ALLEGRO_KEYBOARD_STATE keyboardState;
	//al_get_mouse_state(&mouseState);
	al_get_keyboard_state(&keyboardState);

	if (debug >= 1)
	{
		al_draw_filled_rectangle(100, 50, 300, 180, gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_0);
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, 110, 55, 0, "TIME: %d", GetContainingWorld()->gametime);
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, 110, 95, 0, "TPS: %.1lf", GetContainingWorld()->GetMeasuredTPS());
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, 110, 135, 0, "FPS: %.1lf", DebugInfo::framesEnd.empty() ? 0 : DebugInfo::FRAMES_RECORD_NUM / (DebugInfo::framesEnd.back() - DebugInfo::framesEnd.front()));
	}

	
	float x = GET_MOUSE_XPOS(mousex);
	float y = GET_MOUSE_YPOS(mousey);
	if (debug >= 2)
	{
		al_draw_filled_rectangle(SCREEN_WIDTH / 2 - 500, 50, SCREEN_WIDTH / 2 - 270, 250, gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_1);
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, (SCREEN_WIDTH / 2 - 490), 60, 0, "Chunk X: %d", (int)util_floor(x / WorldChunk::CHUNK_SIZE_X));
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, (SCREEN_WIDTH / 2 - 490), 95, 0, "Chunk Y: %d", (int)util_floor(y / WorldChunk::CHUNK_SIZE_Y));
	}

	Tile* targetedTile = containingWorld->GetTile(floor(x), floor(y));
	GroundTile* targetedGroundTile = containingWorld->GetGroundTile(floor(x), floor(y));
	Entity* targetedEntity = containingWorld->GetEntityAtPos(x, y);
	if (infoMenu)
	{
		al_draw_filled_rectangle(SCREEN_WIDTH / 2 - 250, 50, SCREEN_WIDTH / 2 + 250, 250, al_map_rgba(0, 150, 255, 150));

		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 60, 0, "Player:");
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 20), 60, 0, "X: %.3lf", GetXpos());
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 + 110), 60, 0, "Y: %.3lf", GetYpos());
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 90, 0, "Targeted Tile:");
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 20), 90, 0, "X: %d", (int)floor(x));
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 + 110), 90, 0, "Y: %d", (int)floor(y));
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 150, 0, "Tile:");
		al_draw_textf(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 50), 150, 0, "%s", targetedTile==nullptr?"<NULL>":targetedTile->GetName().c_str());
	}

	if (debug >= 3)
	{
		al_draw_filled_rectangle(SCREEN_WIDTH / 2 + 270, 50, SCREEN_WIDTH / 2 + 600, 250, gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_2);
		al_draw_text(game_GetFont("default", 25), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 60, 0, "WORLD GENERATION INFO");
		al_draw_textf(game_GetFont("default", 20), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 90, 0, "Height: %.4f", containingWorld->GenerateGetLevelHeight(x, y));
		al_draw_textf(game_GetFont("default", 20), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 115, 0, "Humidity: %.4f", containingWorld->GenerateGetLevelHumidity(x, y));
		al_draw_textf(game_GetFont("default", 20), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 140, 0, "Temperature: %.4f", containingWorld->GenerateGetLevelTemperature(x, y));
		al_draw_textf(game_GetFont("default", 20), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 165, 0, "Randomness: %.4f", containingWorld->GenerateGetLevelTileRandomness(x, y));
		al_draw_textf(game_GetFont("default", 20), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 190, 0, "Ore Density: %.4f", containingWorld->GenerateGetLevelOreDensityFactor(x, y));
		al_draw_textf(game_GetFont("default", 20), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, SCREEN_WIDTH / 2 + 280, 215, 0, "Ore Quality: %.4f", containingWorld->GenerateGetLevelOreQualityFactor(x, y));
	}
	if (infoMenu) {
		if (targetedTile != nullptr) {
			if (targetedTile->IsEmpty())
			{
				al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 245), 175, al_map_rgba(150, 150, 150, 150));
				al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 245), 145, al_map_rgba(150, 0, 0, 150));
				//printf("%p::%p\n", GroundTileMiner::GetTarget(), targetedGroundTile);
				if (GroundTileMiner::GetTarget() == targetedGroundTile)
					al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 55 + 190 * GroundTileMiner::GetMiningDamageDone() / targetedGroundTile->GetMiningResistance()), 145, al_map_rgba(255, 0, 0, 150));
			}
			else
			{
				al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 245), 145, al_map_rgba(150, 150, 150, 150));
				al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 245), 175, al_map_rgba(150, 0, 0, 150));
				al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 55 + 190 * (targetedTile->GetMiningDamageDone() / (float)targetedTile->GetMiningResistance())), 175, al_map_rgba(255, 0, 0, 150));
			}
		}
		else
		{
			al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 245), 175, al_map_rgba(150, 150, 150, 150));
			al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 245), 145, al_map_rgba(150, 150, 150, 150));
		}
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, (SCREEN_WIDTH / 2 - 230), 120, 0, "Ground Tile:");
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, (SCREEN_WIDTH / 2 - 50), 120, 0, "%s", targetedGroundTile==nullptr?"<NULL>":targetedGroundTile->GetName().c_str());
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, (SCREEN_WIDTH / 2 - 230), 185, 0, "Entity:");
		al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, (SCREEN_WIDTH / 2 - 100), 185, 0, "%s", (targetedEntity != nullptr) ? targetedEntity->GetName().c_str() : "None");
		if (targetedEntity != nullptr)
		{
			al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 185, (SCREEN_WIDTH / 2 + 55 + 190), 205, gameconfig::PLAYER_MENU_PROGBAR_BACK_COLOR_0);
			al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 185, (SCREEN_WIDTH / 2 + 55 + 190 * (targetedEntity->GetHealth() / targetedEntity->maxHealth)), 205, gameconfig::PLAYER_MENU_PROGBAR_FILL_COLOR_0);
		}
		else
			al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 185, (SCREEN_WIDTH / 2 + 55 + 190), 205, gameconfig::PLAYER_MENU_PROGBAR_BACK_COLOR_1);
	}
	int yn = SCREEN_HEIGHT - 20;
	for (std::list<PlayerNotification*>::reverse_iterator it = notifications.rbegin(); it!=notifications.rend();)
	{
		if ((*it)->ShouldBeRemoved(GUItimer))
		{
			delete (*it);
			notifications.erase(--(it.base()));
		}
		else
		{
			(*it)->Draw(SCREEN_WIDTH - 250, yn -= 80, 200, 70, GUItimer);
			it++;
		}
	}
	const char* m = "";
	switch (mode)
	{
	case PlayerActionMode::COMBAT:
		m = "COMBAT";
		break;
	case PlayerActionMode::MINING:
		m = "MINING";
		break;
	case PlayerActionMode::CONFIGURATION:
		m = "CONFIGURATION";
		break;
	case PlayerActionMode::BUILDING:
		m = "BUILDING";
		break;
	case PlayerActionMode::USE:
		m = "USE";
		break;
	case PlayerActionMode::CONSUME:
		m = "CONSUME";
		break;
	}
	al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, 32, SCREEN_HEIGHT-42, 0, "CURRENT MODE: %s (%s)", m, buildRotation.ToString().c_str());

	switch(guistate)
	{
	case PLAYER_GUI_STATE::WORLD:
	{
		hotbarGUI->DrawGUI();
		switch (mode)
		{
		case PlayerActionMode::COMBAT:
		{
			if (targetedEntity == nullptr)
				al_set_mouse_cursor(main_display, game_GetMouseCursor("ranged"));
			else
				al_set_mouse_cursor(main_display, game_GetMouseCursor("melee"));
			break;
		}
		case PlayerActionMode::CONFIGURATION:
			al_set_mouse_cursor(main_display, game_GetMouseCursor("wrench"));
			break;
		case PlayerActionMode::MINING:
		{
			float a = x - GetXpos();
			float b = y - GetYpos();
			if (a * a + b * b > RANGESQ)
			{
				al_set_mouse_cursor(main_display, game_GetMouseCursor("error"));
				break;
			}
			ToolType t;
			if (targetedTile == nullptr)
				t = ToolType::NONE;
			else
			{
				if (targetedTile->IsEmpty())
					t = targetedGroundTile->GetRequiredToolType();
				else
					t = targetedTile->GetOptimalToolType();
			}
			switch (t)
			{
			case ToolType::PICKAXE:
				al_set_mouse_cursor(main_display, game_GetMouseCursor("pickaxe"));
				break;
			case ToolType::SHOVEL:
				al_set_mouse_cursor(main_display, game_GetMouseCursor("shovel"));
				break;
			case ToolType::AXE:
				al_set_mouse_cursor(main_display, game_GetMouseCursor("axe"));
				break;
			}

			if(showCursorInfoBox)
				if (targetedTile || targetedGroundTile)
				{
					al_draw_filled_rectangle(mousex, mousey, mousex + 200, mousey + 100, gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_0);
					al_draw_textf(game_GetFont("default", 30), gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0, mousex + 100, mousey + 10, ALLEGRO_ALIGN_CENTER, "[%c]%s", targetedTile && !targetedTile->IsEmpty() ? 'T' : 'G', targetedTile && !targetedTile->IsEmpty() ? targetedTile->GetName().c_str() : targetedGroundTile->GetName().c_str());
					float a = targetedTile && !targetedTile->IsEmpty() ? targetedTile->GetMiningDamageDone() : ((targetedGroundTile == GroundTileMiner::GetTarget()) ? GroundTileMiner::GetMiningDamageDone() : 0);
					float b = targetedTile && !targetedTile->IsEmpty() ? targetedTile->GetMiningResistance() : targetedGroundTile->GetMiningResistance();
					DrawUtils::DrawProgressBarWriteValue(mousex + 10, mousey + 70, mousex + 190, mousey + 90, gameconfig::PLAYER_MENU_PROGBAR_FILL_COLOR_0, gameconfig::PLAYER_MENU_PROGBAR_BACK_COLOR_0, game_GetFont("default", 20), al_map_rgba(255, 255, 255, 255), DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT_RATIO, b-a, b);
				}
			
			break;
		}
		case PlayerActionMode::CONSUME:
			al_set_mouse_cursor(main_display, game_GetMouseCursor("use"));
			al_draw_rectangle(SCREEN_WIDTH / 2 - 64 * 1 + 128 * selectedHotbarSlot + SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_HEIGHT - 280 - SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_WIDTH / 2 - 64 * 1 + 128 * selectedHotbarSlot + 128 - SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_HEIGHT - 280 + 128 + SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, al_map_rgba(255,0,0,255), SELECTED_HOTBAR_SLOT_RECT_WIDTH);
			break;
		case PlayerActionMode::BUILDING:
			al_set_mouse_cursor(main_display, game_GetMouseCursor("use"));
			al_draw_rectangle(SCREEN_WIDTH / 2 - 64 * 1 + 128 * selectedHotbarSlot + SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_HEIGHT - 280 - SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_WIDTH / 2 - 64 * 1 + 128 * selectedHotbarSlot + 128 - SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_HEIGHT - 280 + 128 + SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, al_map_rgba(0, 0, 255, 255), SELECTED_HOTBAR_SLOT_RECT_WIDTH);
			break;
		case PlayerActionMode::USE:
			al_draw_rectangle(SCREEN_WIDTH / 2 - 64 * 1 + 128 * selectedHotbarSlot + SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_HEIGHT - 280 - SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_WIDTH / 2 - 64 * 1 + 128 * selectedHotbarSlot + 128 - SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, SCREEN_HEIGHT - 280 + 128 + SELECTED_HOTBAR_SLOT_RECT_WIDTH / 2, al_map_rgba(0, 255, 0, 255), SELECTED_HOTBAR_SLOT_RECT_WIDTH);
			al_set_mouse_cursor(main_display, game_GetMouseCursor("use"));
			break;
		}


		switch (mode)
		{
		case PlayerActionMode::BUILDING:
			placeableHotbarGUI->DrawGUI();
			break;
		case PlayerActionMode::USE:
			usableHotbarGUI->DrawGUI();
			break;
		case PlayerActionMode::CONSUME:
			consumableHotbarGUI->DrawGUI();
			break;
		}

		break;
	}
	case PLAYER_GUI_STATE::INVENTORY:
		al_set_system_mouse_cursor(main_display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(100, 100, 100, 150));
		al_draw_scaled_bitmap(HEALTH_ICON, 0, 0, al_get_bitmap_width(HEALTH_ICON), al_get_bitmap_height(HEALTH_ICON), 0, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(0, SCREEN_HEIGHT / 2 - 300, 64, SCREEN_HEIGHT / 2 + 300, al_map_rgba(64, 0, 0, 200));
		al_draw_filled_rectangle(0, SCREEN_HEIGHT / 2 + 300 - (GetHealth() / 100.f) * 600.f, 64, SCREEN_HEIGHT / 2 + 300, al_map_rgba(192, 0, 0, 200));
		al_draw_scaled_bitmap(HUNGER_ICON, 0, 0, al_get_bitmap_width(HUNGER_ICON), al_get_bitmap_height(HUNGER_ICON), 64, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(64, SCREEN_HEIGHT / 2 - 300, 128, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 64, 0, 200));
		al_draw_filled_rectangle(64, SCREEN_HEIGHT / 2 + 300 - (hunger / MAX_HUNGER) * 600.f, 128, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 192, 0, 200));
		al_draw_scaled_bitmap(WATER_ICON, 0, 0, al_get_bitmap_width(WATER_ICON), al_get_bitmap_height(WATER_ICON), 128, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(128, SCREEN_HEIGHT / 2 - 300, 192, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 0, 64, 200));
		al_draw_filled_rectangle(128, SCREEN_HEIGHT / 2 + 300 - (water / MAX_WATER) * 600.f, 192, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 0, 192, 200));

		//inventoryGUI->DrawGUI();
		recipeGUI->DrawGUI();
		break;
	case PLAYER_GUI_STATE::DEATH:
		break;
	case PLAYER_GUI_STATE::QUEST:
		break;
	case PLAYER_GUI_STATE::CRAFTING:
		break;
	case PLAYER_GUI_STATE::PAUSE:
		al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(100, 100, 100, 150));
		al_draw_scaled_bitmap(HEALTH_ICON, 0, 0, al_get_bitmap_width(HEALTH_ICON), al_get_bitmap_height(HEALTH_ICON), 0, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(0, SCREEN_HEIGHT / 2 - 300, 64, SCREEN_HEIGHT / 2 + 300, al_map_rgba(64, 0, 0, 200));
		al_draw_filled_rectangle(0, SCREEN_HEIGHT / 2 + 300 - (GetHealth() / 100.f) * 600.f, 64, SCREEN_HEIGHT / 2 + 300, al_map_rgba(192, 0, 0, 200));
		al_draw_scaled_bitmap(HUNGER_ICON, 0, 0, al_get_bitmap_width(HUNGER_ICON), al_get_bitmap_height(HUNGER_ICON), 64, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(64, SCREEN_HEIGHT / 2 - 300, 128, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 64, 0, 200));
		al_draw_filled_rectangle(64, SCREEN_HEIGHT / 2 + 300 - (hunger / MAX_HUNGER) * 600.f, 128, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 192, 0, 200));
		al_draw_scaled_bitmap(WATER_ICON, 0, 0, al_get_bitmap_width(WATER_ICON), al_get_bitmap_height(WATER_ICON), 128, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(128, SCREEN_HEIGHT / 2 - 300, 192, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 0, 64, 200));
		al_draw_filled_rectangle(128, SCREEN_HEIGHT / 2 + 300 - (water / MAX_WATER) * 600.f, 192, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 0, 192, 200));
		hotbarGUI->DrawGUI();
		break;
	}
	if (guistate == PLAYER_GUI_STATE::WORLD)
	{
		if (IsTyping())
		{
			al_draw_filled_rectangle(SCREEN_WIDTH / 2 - 510, SCREEN_HEIGHT - 870, SCREEN_WIDTH / 2 + 510, SCREEN_HEIGHT - 410, al_map_rgba(100, 100, 100, 100));
			al_draw_filled_rectangle(SCREEN_WIDTH / 2 - 510, SCREEN_HEIGHT - 410, SCREEN_WIDTH / 2 + 510, SCREEN_HEIGHT - 375, al_map_rgba(50, 50, 50, 150));
			al_draw_text(game_GetFont("default", 30), al_map_rgba(255, 0, 0, 255), SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 410, 0, buf.c_str());
			for (int i = 0; i < history.size(); i++)
				al_draw_text(game_GetFont("default", 30), history.at(i).first, SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT - 445 - i * 30, 0, history.at(i).second.c_str());
		}
		al_draw_scaled_bitmap(HEALTH_ICON, 0, 0, al_get_bitmap_width(HEALTH_ICON), al_get_bitmap_height(HEALTH_ICON), 0, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(0, SCREEN_HEIGHT / 2 - 300, 64, SCREEN_HEIGHT / 2 + 300, al_map_rgba(64, 0, 0, 200));
		al_draw_filled_rectangle(0, SCREEN_HEIGHT / 2 + 300 - (GetHealth() / 100.f) * 600.f, 64, SCREEN_HEIGHT / 2 + 300, al_map_rgba(192, 0, 0, 200));
		al_draw_scaled_bitmap(HUNGER_ICON, 0, 0, al_get_bitmap_width(HUNGER_ICON), al_get_bitmap_height(HUNGER_ICON), 64, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(64, SCREEN_HEIGHT / 2 - 300, 128, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 64, 0, 200));
		al_draw_filled_rectangle(64, SCREEN_HEIGHT / 2 + 300 - (hunger / MAX_HUNGER) * 600.f, 128, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 192, 0, 200));
		al_draw_scaled_bitmap(WATER_ICON, 0, 0, al_get_bitmap_width(WATER_ICON), al_get_bitmap_height(WATER_ICON), 128, SCREEN_HEIGHT / 2 - 364, 64, 64, 0);
		al_draw_filled_rectangle(128, SCREEN_HEIGHT / 2 - 300, 192, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 0, 64, 200));
		al_draw_filled_rectangle(128, SCREEN_HEIGHT / 2 + 300 - (water / MAX_WATER) * 600.f, 192, SCREEN_HEIGHT / 2 + 300, al_map_rgba(0, 0, 192, 200));
	}
	if(guistate==PLAYER_GUI_STATE::WORLD || guistate==PLAYER_GUI_STATE::INVENTORY)
		GUItimer++;
	al_use_transform(&backup_transorm);
	al_unlock_mutex(worldMutex);
}

void PlayerEntity::PostDrawThisGUI()
{

}

void PlayerEntity::Draw()
{
	int x = floor((GetXpos()) * 128);
	int y = floor((GetYpos()) * 128);
	al_draw_rotated_bitmap(TEXTURE, 64, 64, x, y, GetRotation(), 0);
}

bool PlayerEntity::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
	switch (event.keycode)
	{
	case ALLEGRO_KEY_W:
		keys_pressed |= 0b00001000;
		break;
	case ALLEGRO_KEY_A:
		keys_pressed |= 0b00000100;
		break;
	case ALLEGRO_KEY_S:
		keys_pressed |= 0b00000010;
		break;
	case ALLEGRO_KEY_D:
		keys_pressed |= 0b00000001;
		break;
	case ALLEGRO_KEY_Z:
		if (guistate == PLAYER_GUI_STATE::QUEST)
		{
			guistate = PLAYER_GUI_STATE::WORLD;
			activeSubGUI = nullptr;
		}
		else if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			guistate = PLAYER_GUI_STATE::QUEST;
			activeSubGUI = questGUI;
		}
		break;
	case ALLEGRO_KEY_C:
		if (guistate == PLAYER_GUI_STATE::CRAFTING)
		{
			guistate = PLAYER_GUI_STATE::WORLD;
			activeSubGUI = nullptr;
		}
		else if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			activeSubGUI = craftingGUI;
			guistate = PLAYER_GUI_STATE::CRAFTING;
		}
		break;
	case ALLEGRO_KEY_T:
		if (guistate == PLAYER_GUI_STATE::WORLD)
			typing = !typing;
		break;
	case ALLEGRO_KEY_X:
		if (guistate == PLAYER_GUI_STATE::WORLD)
			mode = PlayerActionMode::MINING;
		break;
	case ALLEGRO_KEY_R:
		buildRotation = buildRotation >> 1;
		break;
	case ALLEGRO_KEY_Q:
		if (guistate == PLAYER_GUI_STATE::WORLD)
			mode = PlayerActionMode::COMBAT;
		break;
	case ALLEGRO_KEY_F:
		if (guistate == PLAYER_GUI_STATE::WORLD)
			mode = PlayerActionMode::CONFIGURATION;
		break;
	case ALLEGRO_KEY_E:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			guistate = PLAYER_GUI_STATE::INVENTORY;
			activeSubGUI = inventoryGUI;
		}
		else if (guistate == PLAYER_GUI_STATE::INVENTORY)
		{
			if (inventoryGUI->HasActiveSubGUI())
			{
			
				inventoryGUI->SetActiveSubGUI(nullptr);
				break;
			}
			guistate = PLAYER_GUI_STATE::WORLD;
			activeSubGUI = nullptr;
		}
		break;
	case ALLEGRO_KEY_ALT:
		showCursorInfoBox = true;
		break;
	case ALLEGRO_KEY_ESCAPE:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			guistate = PLAYER_GUI_STATE::PAUSE;
			doWorldTick = false;
			activeSubGUI = pauseGUI;
		}
		else if (guistate == PLAYER_GUI_STATE::PAUSE)
		{
			doWorldTick = true;
			godMode = pauseGUI->godmode_tb->GetIsToggledOn();
			GetContainingWorld()->doTileTick = pauseGUI->tile_tick_tb->GetIsToggledOn();
			GetContainingWorld()->doEntityTick = pauseGUI->entity_tick_tb->GetIsToggledOn();
			guistate = PLAYER_GUI_STATE::WORLD;
			activeSubGUI = nullptr;
		}
		else {
			if (activeSubGUI) {
				activeSubGUI = nullptr;
				guistate = PLAYER_GUI_STATE::WORLD;
			}
		}
		break;
	case ALLEGRO_KEY_F4:
		if (guistate == PLAYER_GUI_STATE::CREATIVE)
		{
			guistate = PLAYER_GUI_STATE::WORLD;
			activeSubGUI = nullptr;
		}
		else
		{
			guistate = PLAYER_GUI_STATE::CREATIVE;
			activeSubGUI = creativeGUI;
		}
		break;
	case ALLEGRO_KEY_F5:
		if (guistate == PLAYER_GUI_STATE::QUEST_EDIT)
		{
			guistate = PLAYER_GUI_STATE::WORLD;
			activeSubGUI = nullptr;
		}
		else
		{
			guistate = PLAYER_GUI_STATE::QUEST_EDIT;
			activeSubGUI = questEditingGUI;
		}
		break;
	case ALLEGRO_KEY_1:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			selectedHotbarSlot = 0;
			if(event.modifiers)
			if (event.modifiers&ALLEGRO_KEYMOD_ALT)
				mode = PlayerActionMode::USE;
			else if (event.modifiers & ALLEGRO_KEYMOD_CTRL)
				mode = PlayerActionMode::CONSUME;
			else
				mode = PlayerActionMode::BUILDING;
		}
		break;
	case ALLEGRO_KEY_2:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			selectedHotbarSlot = 1;
			if (event.modifiers & ALLEGRO_KEYMOD_ALT)
				mode = PlayerActionMode::USE;
			else if (event.modifiers & ALLEGRO_KEYMOD_CTRL)
				mode = PlayerActionMode::CONSUME;
			else
				mode = PlayerActionMode::BUILDING;
		}
		break;
	case ALLEGRO_KEY_3:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			selectedHotbarSlot = 2;
			if (event.modifiers & ALLEGRO_KEYMOD_ALT)
				mode = PlayerActionMode::USE;
			else if (event.modifiers & ALLEGRO_KEYMOD_CTRL)
				mode = PlayerActionMode::CONSUME;
			else
				mode = PlayerActionMode::BUILDING;
		}
		break;
	case ALLEGRO_KEY_4:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			selectedHotbarSlot = 3;
			if (event.modifiers & ALLEGRO_KEYMOD_ALT)
				mode = PlayerActionMode::USE;
			else if (event.modifiers & ALLEGRO_KEYMOD_CTRL)
				mode = PlayerActionMode::CONSUME;
			else
				mode = PlayerActionMode::BUILDING;
		}
		break;
	case ALLEGRO_KEY_5:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			selectedHotbarSlot = 4;
			if (event.modifiers & ALLEGRO_KEYMOD_ALT)
				mode = PlayerActionMode::USE;
			else if (event.modifiers & ALLEGRO_KEYMOD_CTRL)
				mode = PlayerActionMode::CONSUME;
			else
				mode = PlayerActionMode::BUILDING;
		}
		break;
	case ALLEGRO_KEY_6:

		break;
	case ALLEGRO_KEY_7:

		break;
	case ALLEGRO_KEY_8:

		break;
	case ALLEGRO_KEY_9:

		break;
	case ALLEGRO_KEY_F1:
		infoMenu = !infoMenu;
		break;
	case ALLEGRO_KEY_F2:
		showHitbox = !showHitbox;
		break;
	case ALLEGRO_KEY_F3:
		debug = (debug + ((event.modifiers&ALLEGRO_KEYMOD_SHIFT)?-1:1)+4) % 4;
		break;
	}
	return true;
}

bool PlayerEntity::KeyUp(ALLEGRO_KEYBOARD_EVENT& event)
{
	switch (event.keycode)
	{
	case ALLEGRO_KEY_W:
		keys_pressed &= 0b11110111;
		break;
	case ALLEGRO_KEY_A:
		keys_pressed &= 0b11111011;
		break;
	case ALLEGRO_KEY_S:
		keys_pressed &= 0b11111101;
		break;
	case ALLEGRO_KEY_D:
		keys_pressed &= 0b11111110;
		break;
	case ALLEGRO_KEY_ALT:
		showCursorInfoBox = false;
		break;
	}
	return true;
}



bool PlayerEntity::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if (guistate == PLAYER_GUI_STATE::WORLD)
	{
		float x = GET_MOUSE_XPOS(event.x);
		float y = GET_MOUSE_YPOS(event.y);
		switch (mode)
		{
		case PlayerActionMode::COMBAT:
		{
			switch (event.button)
			{
			case 1:
			{
				Entity* e = containingWorld->GetEntityAtPos(x, y, this);
				if (e != nullptr)
				{
					MeleeWeapon* mw = dynamic_cast<MeleeWeapon*>(meleeWeapon);
					if (mw != nullptr)
					{
						float a = e->GetXpos() - GetXpos();
						float b = e->GetYpos() - GetYpos();
						if (a * a + b * b <= mw->GetRangeSQ())
							e->DoDamage(mw);
						if (e->GetHealth() <= 0.f)
						{
							AddResult(e->GetKillingDrops());
							if (GetContainingWorld()->GetQuestCollection() != nullptr)
								GetContainingWorld()->GetQuestCollection()->EntityKilled(e);
						}
					}
				}
			}
			break;
			case 2:
			{
				UseTile(floor(GET_MOUSE_XPOS(event.x)), floor(GET_MOUSE_YPOS(event.y)));
				break;
			}
			}
			break;
		}
		case PlayerActionMode::MINING:
		{

			switch (event.button)
			{
			case 1:
			{
				float a = x - GetXpos();
				float b = y - GetYpos();
				if (a * a + b * b <= RANGESQ)
					MineTile(floor(x), floor(y));
				break;
			}
			case 2:
			{

				break;
			}
			}
			break;
		}
		case PlayerActionMode::CONFIGURATION:
		{

			switch (event.button)
			{
			case 1:
			{
				UseTile(floor(x), floor(y));
				break;
			}
			case 2:
			{
				UseTile(floor(x), floor(y));
				break;
			}
			}
			break;
		}
		case PlayerActionMode::BUILDING:
		{
			PlaceableItem* pi = dynamic_cast<PlaceableItem*>(placeablesInventory->GetItem(selectedHotbarSlot));
			if (pi == nullptr)
				break;
			if (pi->Use(x, y, this))
			{
				pi->RemoveAmount(1);
				if (pi->GetAmount() <= 0)
				{
					delete pi;
					placeablesInventory->SetItem(selectedHotbarSlot, nullptr);
				}
			}
			break;
		}
		case PlayerActionMode::USE:
		{
			switch (event.button)
			{
			case 1:
			{
				Item* i = usablesInventory->GetItem(selectedHotbarSlot);
				Usable* u = dynamic_cast<Usable*>(i);
				if (u != nullptr)
					if (u->Use(GET_MOUSE_XPOS(event.x), GET_MOUSE_YPOS(event.y), this))
					{
						i->RemoveAmount(1);
						if (i->GetAmount() <= 0)
						{
							delete u;
							usablesInventory->SetItem(selectedHotbarSlot, nullptr);
						}
					}
				break;
			}
			break;
			case 2:
			{
				UseTile(floor(GET_MOUSE_XPOS(event.x)), floor(GET_MOUSE_YPOS(event.y)));
				break;
			}
			}
			break;
		}
		case PlayerActionMode::CONSUME:
			{
			switch (event.button) {
			case 1:
			{
				Item* i = consumablesInventory->GetItem(selectedHotbarSlot);
				Consumable* c = dynamic_cast<Consumable*>(i);
				if (c != nullptr)
					if (c->Consume(GetXpos(), GetYpos(), this))
					{
						i->RemoveAmount(1);
						if (i->GetAmount() <= 0)
						{
							delete i;
							consumablesInventory->SetItem(selectedHotbarSlot, nullptr);
						}
					}
				break;
			}
			case 2:
			{
				Item* i = consumablesInventory->GetItem(selectedHotbarSlot);
				Usable* u = dynamic_cast<Usable*>(i);
				if (u != nullptr) {
					if (u->Use(GET_MOUSE_XPOS(event.x), GET_MOUSE_YPOS(event.y), this))
					{
						i->RemoveAmount(1);
						if (i->GetAmount() <= 0)
						{
							delete i;
							usablesInventory->SetItem(selectedHotbarSlot, nullptr);
						}
					}
				}
				else
				{
					Consumable* c = dynamic_cast<Consumable*>(i);
					if (c != nullptr)
						if (c->Consume(GetXpos(), GetYpos(), this))
						{
							i->RemoveAmount(1);
							if (i->GetAmount() <= 0)
							{
								delete c;
								consumablesInventory->SetItem(selectedHotbarSlot, nullptr);
							}
						}
				}
				break;
			}
			}
		}
		}
	}
	return true;
}

bool PlayerEntity::MouseButtonUp(ALLEGRO_MOUSE_EVENT& event)
{
	return true;
}

bool PlayerEntity::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	if (guistate == PLAYER_GUI_STATE::WORLD)
		rotateTo(atan2((event.y - (SCREEN_HEIGHT / 2)), ((float)event.x - (SCREEN_WIDTH / 2))) + M_PI / 2);
	return true;
}
/*

	else if (guistate == PLAYER_GUI_STATE::INVENTORY)
		inventoryGUI->MouseButtonDown(event);
	else if (guistate == PLAYER_GUI_STATE::QUEST)
		questGUI->MouseButtonDown(event);
	else if (guistate == PLAYER_GUI_STATE::CRAFTING)
		craftingGUI->MouseButtonDown(event);
		
		
	else if (guistate == PLAYER_GUI_STATE::QUEST)
		questGUI->MouseButtonMove(event);
		
		
		
*/


bool PlayerEntity::KeyChar(ALLEGRO_KEYBOARD_EVENT& event)
{
	if (event.keycode == ALLEGRO_KEY_ESCAPE)
	{
		ToggleTyping();
		return true;
	}
	if (event.keycode == ALLEGRO_KEY_BACKSPACE)
	{
		if (buf.size())
			buf.pop_back();
		return true;
	}
	if (event.keycode == ALLEGRO_KEY_ENTER)
	{
		history.push_front(std::make_pair(al_map_rgba(200, 0, 0, 255), buf));
		luaInterface->dostring(buf);
		while (history.size() > 15)
			history.pop_back();
		buf.clear();
		return true;
	}
	buf.push_back(event.unichar);
	return true;
}

/*
void PlayerEntity::AddConstItem(Item* item)
{
	if (item == nullptr)
		return;
	notifications.push_back(PlayerNotification::MakeTextNotification(std::format("+{} {}",item->GetAmount(), item->GetName()), 200, 70, GUItimer+500));
	inventory->AddConstItem(item);
	return;
}
*/

static const float DIAG_MOD = 1.4142135623730950488016887242097 / 2;
static const float PLAYER_SPEED = 0.006f;

void PlayerEntity::UseTile(int x, int y)
{
	float a = GetXpos() - x;
	float b = GetYpos() - y;
	if (a * a + b * b > RANGESQ)
		return;
	Tile* tile = containingWorld->GetTile(x, y);
	if (tile->IsEmpty())
	{
		GroundTile* gtile = containingWorld->GetGroundTile(x, y);
		gtile->Use(this);
	}
	else
		tile->Use(this);
}

void PlayerEntity::MineTile(int x, int y)
{
	float a = xpos - x;
	float b = ypos - y;
	Tile* tile = containingWorld->GetTile(x, y);
	if (tile == nullptr)
		return;
	if (tile->IsEmpty())
	{
		SetTarget(containingWorld,x,y);
		if(GroundTileMiner::GetTarget())
			switch (GroundTileMiner::GetTarget()->GetRequiredToolType()) {
			case Tool::ToolType::PICKAXE:
				GroundTileMiner::SetTool(dynamic_cast<ToolItem*>(pickaxeTool));
				break;
			case Tool::ToolType::SHOVEL:
				GroundTileMiner::SetTool(dynamic_cast<ToolItem*>(shovelTool));
				break;
			case Tool::ToolType::AXE:
				GroundTileMiner::SetTool(dynamic_cast<ToolItem*>(axeTool));
				break;
			}
		this->Mine();
		return;
	}
	GroundTileMiner::ResetProgress();
	bool success = false;
	Tool* t = nullptr;
	switch (tile->GetOptimalToolType())
	{
	case ToolType::PICKAXE:
		t = dynamic_cast<ToolItem*>(pickaxeTool);
		break;
	case ToolType::AXE:
		t = dynamic_cast<ToolItem*>(axeTool);
		break;
	case ToolType::SHOVEL:
		t = dynamic_cast<ToolItem*>(shovelTool);
		break;
	case ToolType::PUMP:
		t = dynamic_cast<ToolItem*>(pumpTool);
		break;
	case ToolType::NONE:
		break;
	}
	success = tile->MineWithTool(t);
	if (success)
	{
		if (GetContainingWorld()->GetQuestCollection() != nullptr)
			GetContainingWorld()->GetQuestCollection()->TileMined(tile, t);
		const ItemBundle* b = tile->GetMiningResult(nullptr);
		if(b!=nullptr)
		for (int i = 0; i < b->GetSize(); i++)
			GiveConstItem(b->GetItem(i));
		containingWorld->RemoveTile(x, y);
	}
}

Direction PlayerEntity::GetBuildingRotation() const
{
	return buildRotation;
}
	
void PlayerEntity::GiveConstItem(const Item* item)
{
	if (item == nullptr)
		return;
	if (item->GetAmount() == 0)
	{
		delete item;
		return;
	}
	PushNotification(std::format("+{} {}", item->GetAmount(), item->GetName()));
	inventory->AddConstItem(item);
}

Item* PlayerEntity::GiveItem(Item* item)
{
	if (item == nullptr)
		return nullptr;
	if (item->GetAmount() == 0)
	{
		delete item;
		return nullptr;
	}
	PushNotification(std::format("+{} {}", item->GetAmount(), item->GetName()));
	return inventory->AddItem(item);
}

void PlayerEntity::GiveConstItemBundle(const ItemBundle* bundle)
{
	for (int i = 0; i < bundle->GetSize(); i++)
		GiveConstItem(bundle->GetItem(i));
}

void PlayerEntity::Tick()
{
	if (Entity::IsDead())
	{
		guistate = PLAYER_GUI_STATE::DEATH;
		activeSubGUI = deathgui;
	}
	else
	{
		switch (keys_pressed & 0b00001111)
		{
		case 0b0001:
			ApplyForce(PLAYER_SPEED, 0);
			break;
		case 0b0010:
			ApplyForce(0, PLAYER_SPEED);
			break;
		case 0b0011:
			ApplyForce(PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
			break;
		case 0b0100:
			ApplyForce(-PLAYER_SPEED, 0);
			break;
		case 0b0110:
			ApplyForce(-PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
			break;
		case 0b1000:
			ApplyForce(0, -PLAYER_SPEED);
			break;
		case 0b1001:
			ApplyForce(PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
			break;
		case 0b1100:
			ApplyForce(-PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
			break;
		}
		if (!godMode)
		{
			hunger = std::max(0.f, hunger - HUNGER_LOSS_PER_TICK);
			if (hunger == 0.f)
			{
				DoDamage(HEALTH_LOSS_FROM_HUNGER_PER_TICK);
			}
			water = std::max(0.f, water - WATER_LOSS_PER_TICK);
			if (water == 0.f)
			{
				DoDamage(HEALTH_LOSS_FROM_WATER_PER_TICK);
			}
		}
		else
		{
			hunger = MAX_HUNGER;
			water = MAX_WATER;
			SetHealth(GetMaxHealth());
		}
		Entity::Tick();
	}
	if(GetContainingWorld()->GetQuestCollection()!=nullptr)
		GetContainingWorld()->GetQuestCollection()->Update();
}

void PlayerEntity::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	MAX_WATER = data["max_water"];
	WATER_LOSS_PER_TICK = data["water_loss_per_tick"];
	HEALTH_LOSS_FROM_WATER_PER_TICK = data["health_loss_from_water_per_tick"];
	MAX_HUNGER = data["max_hunger"];
	HUNGER_LOSS_PER_TICK = data["hunger_loss_per_tick"];
	HEALTH_LOSS_FROM_HUNGER_PER_TICK = data["health_loss_from_hunger_per_tick"];
	RANGESQ = data[DATA_JSON_RANGESQ_KEY];
	AUDIO_TRACKS.LoadFromJSON(data[DATA_JSON_AUDIO_COLLECTION_KEY]);
}

void PlayerEntity::ResetAfterDeath()
{
	this->guistate = PLAYER_GUI_STATE::WORLD;
	activeSubGUI = nullptr;
	warpAbsolute(0, 0);
	hunger = MAX_HUNGER;
	water = MAX_WATER;
	Revive();
}

void PlayerEntity::PlaySound(SoundType t) const
{
	AUDIO_TRACKS.Play(t);
}

void PlayerEntity::PushNotification(std::string txt, int fontsize)
{
	notifications.push_back(PlayerNotification::MakeTextNotification(txt, 200, 70, GUItimer + 2000, fontsize));
}

void PlayerEntity::DisplayTileGUI(Tile* t, GUI* g)
{
	guistate = PLAYER_GUI_STATE::TILE;
	activeSubGUI = g;
}

InventoryGUI* PlayerEntity::GetMainInventoryGUI(int offsetx, int offsety)
{
	InventoryGUI* g = new InventoryGUI();
	for (int i = 0; i < 9; i++)
	{
		g->AddSlot(128 * i + offsetx, 0 + offsety, 128, 128, *inventory->GetItemPtr(i), InventoryGUI::StorageSlotType::GENERIC);
		g->AddSlot(128 * i + offsetx, 128 + offsety, 128, 128, *inventory->GetItemPtr(i + 9), InventoryGUI::StorageSlotType::GENERIC);
		g->AddSlot(128 * i + offsetx, 256 + offsety, 128, 128, *inventory->GetItemPtr(i + 18), InventoryGUI::StorageSlotType::GENERIC);
	}
	return g;
}

void PlayerEntity::ShowItemDescription(const Item* i)
{
	itemInfoGUI->SetTargetItem(i);
	OpenGUITop(itemInfoGUI);
}

PlayerEntity::PlayerEntity(World* world, float xpos, float ypos) : Entity(world, xpos, ypos, 100.f, 1.f, 0.f, 0.f, .5f, .5f), GUItimer{ 0 }, axeTool{ nullptr }, pickaxeTool{ nullptr }, shovelTool{ nullptr }, pumpTool{ nullptr }, guistate{ PLAYER_GUI_STATE::WORLD }, keys_pressed{ 0b00000000 }, GroundTileMiner(nullptr, nullptr, containingWorld, 0, 0), mode{ PlayerActionMode::MINING }, selectedHotbarSlot{ 0 }, stashedItem{ nullptr }
{
	GUI_GLOBAL_PLAYER_OBJECT = this;
	hunger = MAX_HUNGER;
	water = MAX_WATER;
	SetName("Player");
	if (world == nullptr)
		return;
	luaInterface = new LuaInterface(world, true);
	inventory = new SimpleItemInventory(27);
	usablesInventory = new SimpleItemInventory(5);
	consumablesInventory = new SimpleItemInventory(5);
	placeablesInventory = new SimpleItemInventory(5);
	meleeWeapon = nullptr;
	rangedWeapon = nullptr;
	itemInfoGUI = new ItemInfoGUI();
	GroundTileMiner::SetTargetItemInventory(inventory);
	inventoryGUI = new InventoryGUI();
	hotbarGUI = new InventoryGUI();
	hotbarGUI->SetShowStashedItem(false);
	consumableHotbarGUI = new InventoryGUI();
	usableHotbarGUI = new InventoryGUI();
	placeableHotbarGUI = new InventoryGUI();
	pauseGUI = new PauseMenuGUI(this);
	questEditingGUI = new QuestEditingGUI(this);
	questEditingGUI->SetQuestCollection(GetContainingWorld()->GetQuestCollection());
	creativeGUI = new CreativeItemGUI(this);
	creativeGUI->SetItemsList(prototype_items);
	craftingGUI = new SimpleCraftingGUI();
	craftingGUI->SetRecipeList(loaded_crafting_recipes);
	craftingGUI->SetInventory(inventory);
	craftingGUI->SetRecipeCallbackFunction([&](const CraftingRecipe* recipe, int times) {
		if (times == 0)
			return;
		for (int i = 0; i < recipe->GetInputItems()->GetSize(); i++)
			PushNotification(std::format("-{} x {}", recipe->GetInputItems()->GetItem(i)->GetAmount()*times, recipe->GetInputItems()->GetItem(i)->GetName()));
		for (int i = 0; i < recipe->GetOutputItems()->GetSize(); i++)
			PushNotification(std::format("+{} x {}", recipe->GetOutputItems()->GetItem(i)->GetAmount()*times, recipe->GetOutputItems()->GetItem(i)->GetName()));
	});
	activeSubGUI = nullptr;
	deathgui = new DeathGUI(this);
	if (GetContainingWorld()->GetQuestCollection() != nullptr)
		questGUI = new QuestGUI(GetContainingWorld()->GetQuestCollection());
	else
		questGUI = new QuestGUI(QuestCollection::GetNullCollection());
	for (int i = 0; i < 9; i++)
	{
		inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT / 2 - 192, 128, 128, *inventory->GetItemPtr(i), InventoryGUI::StorageSlotType::GENERIC);
		inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT / 2 - 64, 128, 128, *inventory->GetItemPtr(i+9), InventoryGUI::StorageSlotType::GENERIC);
		inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT / 2 + 64, 128, 128, *inventory->GetItemPtr(i+18), InventoryGUI::StorageSlotType::GENERIC);
	}
	hotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9, SCREEN_HEIGHT - 280, 128, 128, meleeWeapon, InventoryGUI::StorageSlotType::MELEE);
	hotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 7, SCREEN_HEIGHT - 280, 128, 128, rangedWeapon, InventoryGUI::StorageSlotType::RANGED);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9, SCREEN_HEIGHT - 280, 128, 128, meleeWeapon, InventoryGUI::StorageSlotType::MELEE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 7, SCREEN_HEIGHT - 280, 128, 128, rangedWeapon, InventoryGUI::StorageSlotType::RANGED);

	hotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9, SCREEN_HEIGHT - 152, 128, 128, pickaxeTool, InventoryGUI::StorageSlotType::PICKAXE);
	hotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 7, SCREEN_HEIGHT - 152, 128, 128, shovelTool, InventoryGUI::StorageSlotType::SHOVEL);
	hotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 5, SCREEN_HEIGHT - 152, 128, 128, axeTool, InventoryGUI::StorageSlotType::AXE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 9, SCREEN_HEIGHT - 152, 128, 128, pickaxeTool, InventoryGUI::StorageSlotType::PICKAXE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 7, SCREEN_HEIGHT - 152, 128, 128, shovelTool, InventoryGUI::StorageSlotType::SHOVEL);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 5, SCREEN_HEIGHT - 152, 128, 128, axeTool, InventoryGUI::StorageSlotType::AXE);

	placeableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *placeablesInventory->GetItemPtr(0), InventoryGUI::StorageSlotType::PLACEABLE);
	placeableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *placeablesInventory->GetItemPtr(1), InventoryGUI::StorageSlotType::PLACEABLE);
	placeableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 3, SCREEN_HEIGHT - 280, 128, 128, *placeablesInventory->GetItemPtr(2), InventoryGUI::StorageSlotType::PLACEABLE);
	placeableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 5, SCREEN_HEIGHT - 280, 128, 128, *placeablesInventory->GetItemPtr(3), InventoryGUI::StorageSlotType::PLACEABLE);
	placeableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 7, SCREEN_HEIGHT - 280, 128, 128, *placeablesInventory->GetItemPtr(4), InventoryGUI::StorageSlotType::PLACEABLE);

	usableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(0), InventoryGUI::StorageSlotType::USABLE);
	usableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(1), InventoryGUI::StorageSlotType::USABLE);
	usableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 3, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(2), InventoryGUI::StorageSlotType::USABLE);
	usableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 5, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(3), InventoryGUI::StorageSlotType::USABLE);
	usableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 7, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(4), InventoryGUI::StorageSlotType::USABLE);

	consumableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *consumablesInventory->GetItemPtr(0), InventoryGUI::StorageSlotType::CONSUMABLE);
	consumableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *consumablesInventory->GetItemPtr(1), InventoryGUI::StorageSlotType::CONSUMABLE);
	consumableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 3, SCREEN_HEIGHT - 280, 128, 128, *consumablesInventory->GetItemPtr(2), InventoryGUI::StorageSlotType::CONSUMABLE);
	consumableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 5, SCREEN_HEIGHT - 280, 128, 128, *consumablesInventory->GetItemPtr(3), InventoryGUI::StorageSlotType::CONSUMABLE);
	consumableHotbarGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 7, SCREEN_HEIGHT - 280, 128, 128, *consumablesInventory->GetItemPtr(4), InventoryGUI::StorageSlotType::CONSUMABLE);

	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 1, SCREEN_HEIGHT - 408, 128, 128, *placeablesInventory->GetItemPtr(0), InventoryGUI::StorageSlotType::PLACEABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 1, SCREEN_HEIGHT - 408, 128, 128, *placeablesInventory->GetItemPtr(1), InventoryGUI::StorageSlotType::PLACEABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 3, SCREEN_HEIGHT - 408, 128, 128, *placeablesInventory->GetItemPtr(2), InventoryGUI::StorageSlotType::PLACEABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 5, SCREEN_HEIGHT - 408, 128, 128, *placeablesInventory->GetItemPtr(3), InventoryGUI::StorageSlotType::PLACEABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 7, SCREEN_HEIGHT - 408, 128, 128, *placeablesInventory->GetItemPtr(4), InventoryGUI::StorageSlotType::PLACEABLE);

	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(0), InventoryGUI::StorageSlotType::USABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 1, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(1), InventoryGUI::StorageSlotType::USABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 3, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(2), InventoryGUI::StorageSlotType::USABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 5, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(3), InventoryGUI::StorageSlotType::USABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 7, SCREEN_HEIGHT - 280, 128, 128, *usablesInventory->GetItemPtr(4), InventoryGUI::StorageSlotType::USABLE);

	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 - 64 * 1, SCREEN_HEIGHT - 152, 128, 128, *consumablesInventory->GetItemPtr(0), InventoryGUI::StorageSlotType::CONSUMABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 1, SCREEN_HEIGHT - 152, 128, 128, *consumablesInventory->GetItemPtr(1), InventoryGUI::StorageSlotType::CONSUMABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 3, SCREEN_HEIGHT - 152, 128, 128, *consumablesInventory->GetItemPtr(2), InventoryGUI::StorageSlotType::CONSUMABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 5, SCREEN_HEIGHT - 152, 128, 128, *consumablesInventory->GetItemPtr(3), InventoryGUI::StorageSlotType::CONSUMABLE);
	inventoryGUI->AddSlot(SCREEN_WIDTH / 2 + 64 * 7, SCREEN_HEIGHT - 152, 128, 128, *consumablesInventory->GetItemPtr(4), InventoryGUI::StorageSlotType::CONSUMABLE);

	inventoryGUI->AddCallbackSlot(SCREEN_WIDTH / 2 + 9 * 64, SCREEN_HEIGHT - 152, 128, 128, [this](Item* item) {
		Consumable* c = dynamic_cast<Consumable*>(item);
		if (c == nullptr)
			return item;
		if (c->Consume(GetXpos(), GetYpos(), this))
		{
			item->RemoveAmount(1);
			if (item->GetAmount() <= 0)
			{
				delete item;
				return (Item*)nullptr;
			}
		}
		return item;
		},
		[this](Item* item) {
		Consumable* c = dynamic_cast<Consumable*>(item);
		if (c == nullptr)
			return item;
		if (c->Consume(GetXpos(), GetYpos(), this))
		{
			item->RemoveAmount(1);
			if (item->GetAmount() <= 0)
			{
				delete item;
				return (Item*)nullptr;
			}
		}
		return item;
	});
	inventoryGUI->AddTrashSlot(SCREEN_WIDTH / 2 + 9*64, SCREEN_HEIGHT - 280, 128, 128);
	recipeGUI = new SimpleRecipeListGUI(SCREEN_WIDTH/2+576,256,128,128);
	//recipeGUI->SetRecipeList(loaded_crafting_recipes);
	TEXTURE = game_GetTexture("tex.entities.player");
	HEALTH_ICON = game_GetTexture("tex.gui.health_icon");
	HUNGER_ICON = game_GetTexture("tex.gui.hunger_icon");
	WATER_ICON = game_GetTexture("tex.gui.water_icon");
	GUI_GLOBAL_PLAYER_INVENTORY_HOVER_GUI = GetMainInventoryGUI(SCREEN_WIDTH/2-9*64,SCREEN_HEIGHT/2-3*64);
}

PlayerNotification::PlayerNotification(int t, int w, int h)
{
	timer = t;
	content = al_create_bitmap(w, h);
}

void PlayerNotification::Draw(int x, int y, int width, int height, int new_timer)
{
	al_draw_scaled_bitmap(content, 0, 0, al_get_bitmap_width(content), al_get_bitmap_height(content), x, y, width, height, 0);
}

bool PlayerNotification::ShouldBeRemoved(int new_timer)
{
	return timer<new_timer;
}

PlayerNotification* PlayerNotification::MakeTextNotification(std::string txt, int w, int h, int t, int fontsize)
{
	PlayerNotification* p = new PlayerNotification(t, w, h);
	ALLEGRO_BITMAP* b = al_get_target_bitmap();
	al_set_target_bitmap(p->content);
	al_clear_to_color(al_map_rgba(200, 200, 20, 170));
	al_draw_multiline_text(game_GetFont("default", fontsize), al_map_rgba(0, 0, 0, 255), 10, 10, w - 20, h - 20, 0, txt.c_str());
	al_set_target_bitmap(b);
	return p;
}

PlayerNotification::~PlayerNotification()
{
	al_destroy_bitmap(content);
}

void PlayerEntity::PauseMenuGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(150, 150, 150, 150));
}

#include "AllegroGame.h"

PlayerEntity::PauseMenuGUI::PauseMenuGUI(PlayerEntity* p)
{
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 300, 300, 100, [this,p]() {
		doWorldTick = true;
		p->godMode = godmode_tb->GetIsToggledOn();
		p->GetContainingWorld()->doTileTick = tile_tick_tb->GetIsToggledOn();
		p->GetContainingWorld()->doEntityTick = entity_tick_tb->GetIsToggledOn();
		p->guistate = PLAYER_GUI_STATE::WORLD;
		p->activeSubGUI = nullptr;
		}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "RESUME GAME"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 100, [p]() {
		ALLEGRO_FILECHOOSER* f = al_create_native_file_dialog("", "SAVE WORLD", "*.zip", ALLEGRO_FILECHOOSER_SAVE);
		if (al_show_native_file_dialog(main_display, f)) {
			p->containingWorld->SaveToFile(al_get_native_file_dialog_path(f, 0));
			p->PushNotification("SUCCESSFULLY SAVED WORLD!!!", 24);
		}
		else
			p->PushNotification("FAILED TO SAVE WORLD!!!", 24);
		al_destroy_native_file_dialog(f);
		}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "SAVE WORLD"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 300, 100, [p]() {
		ALLEGRO_FILECHOOSER* f = al_create_native_file_dialog("", "SAVE WORLD", "*.zip", ALLEGRO_FILECHOOSER_SAVE);
		if (al_show_native_file_dialog(main_display, f)) {
			p->containingWorld->SaveToFile(al_get_native_file_dialog_path(f, 0));
			p->PushNotification("SUCCESSFULLY SAVED WORLD!!!", 24);
			al_destroy_native_file_dialog(f);
			delete p->GetContainingWorld();
			::world = nullptr;
			al_stop_samples();
			al_play_sample(loaded_audio_samples["themes.menu"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
			currentGUI = mainMenuGUI;
		}
		else
		{
			p->PushNotification("FAILED TO SAVE WORLD!!!", 24);
			al_destroy_native_file_dialog(f);
		}
		}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "SAVE AND EXIT"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 150, 300, 100, [p]() {
		delete p->GetContainingWorld();
		::world = nullptr;
		al_stop_samples();
		al_play_sample(loaded_audio_samples["themes.menu"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
		currentGUI = mainMenuGUI;
		}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "EXIT WITHOUT SAVING"));
	UIcomponents.push_back(godmode_tb = new SimpleToggleTextButtonUIComponent(100, SCREEN_HEIGHT / 2 - 100, 400, 50, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "GOD-MODE", false));
	UIcomponents.push_back(tile_tick_tb = new SimpleToggleTextButtonUIComponent(100, SCREEN_HEIGHT / 2 - 25, 400, 50, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "DO TILE TICK", true));
	UIcomponents.push_back(entity_tick_tb = new SimpleToggleTextButtonUIComponent(100, SCREEN_HEIGHT / 2 + 50, 400, 50, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "DO ENTITY TICK", true));
}


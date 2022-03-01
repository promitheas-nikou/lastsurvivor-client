#include "PlayerEntity.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "ResourceLoader.h"
#include "SimpleButtonUIComponent.h"
#include "SimpleItemInventory.h"
#include "SimpleInventoryGUI.h"
#include "Graphics.h"
#include "World.h"
#define _USE_MATH_DEFINES
#include <math.h>

ALLEGRO_BITMAP* PlayerEntity::TEXTURE;

int a, b, c;

#define GET_MOUSE_XPOS(E) (E.x / 128.f + GetXpos() - (SCREEN_WIDTH / 256.f))
#define GET_MOUSE_YPOS(E) (E.y / 128.f + GetYpos() - (SCREEN_HEIGHT / 256.f))

std::string buf = "";
void PlayerEntity::DrawThisGUI()
{
	static ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	al_get_blender(&a, &b, &c);
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	al_draw_filled_rectangle(SCREEN_WIDTH/2-250, 50, SCREEN_WIDTH/2+250, 250, al_map_rgba(0, 150, 255, 150));

	float x = GET_MOUSE_XPOS(mouseState);
	float y = GET_MOUSE_YPOS(mouseState);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 60, 0, "Player:");
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 20), 60, 0, "X: %.3lf", GetXpos());
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 + 110), 60, 0, "Y: %.3lf", GetYpos());
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 90, 0, "Targeted Tile:");
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 20), 90, 0, "X: %d", (int)floor(x));
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 + 110), 90, 0, "Y: %d", (int)floor(y));
	Tile* targetedTile = containingWorld->GetTile(floor(x), floor(y));
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 150, 0, "Tile:");
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 50), 150, 0, "%s",targetedTile->GetName().c_str());
	if (targetedTile->IsEmpty())
	{
		GroundTile* targetedGroundTile = containingWorld->GetGroundTile(floor(x), floor(y));
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
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 120, 0, "Ground Tile:");
	al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 50), 120, 0, "%s", containingWorld->GetGroundTile(floor(x),floor(y))->GetName().c_str());
	al_set_blender(a, b, c);

	int yn = SCREEN_HEIGHT - 20;
	for (std::list<PlayerNotification*>::iterator it = notifications.begin(); it!=notifications.end();)
	{
		if ((*it)->ShouldBeRemoved(GUItimer))
		{
			std::list<PlayerNotification*>::iterator tmp = it;
			tmp++;
			notifications.erase(it);
			it = tmp;
		}
		else
		{
			(*it)->Draw(SCREEN_WIDTH - 250, yn -= 80, 200, 70, GUItimer);
			it++;
		}
	}
	if(guistate==PLAYER_GUI_STATE::WORLD)
		hotbarGUI->DrawGUI();
	else
		inventoryGUI->DrawGUI();
	GUItimer++;

	al_draw_text(loaded_fonts["default"][30], al_map_rgba(255, 0, 0, 255), 500, SCREEN_HEIGHT - 500, 0, buf.c_str());
}

void PlayerEntity::Draw()
{
	int x = floor(GetXpos() * 128);
	int y = floor(GetYpos() * 128);
	al_draw_rotated_bitmap(TEXTURE, 64, 64, x, y, getRotation(), 0);
}

void PlayerEntity::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
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
	case ALLEGRO_KEY_T:
		typing=!typing;
		break;
	case ALLEGRO_KEY_E:
		if (guistate == PLAYER_GUI_STATE::WORLD)
		{
			guistate = PLAYER_GUI_STATE::INVENTORY;
		}
		else if (guistate == PLAYER_GUI_STATE::INVENTORY)
		{
			guistate = PLAYER_GUI_STATE::WORLD;
		}
		break;
	}
}

void PlayerEntity::KeyUp(ALLEGRO_KEYBOARD_EVENT& event)
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
	}
}



void PlayerEntity::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if (guistate == PLAYER_GUI_STATE::WORLD)
	{
		switch (event.button)
		{
		case 1:
			MineTile(floor(GET_MOUSE_XPOS(event)), floor(GET_MOUSE_YPOS(event)));
			break;
		case 2:
			PlaceTile(floor(GET_MOUSE_XPOS(event)), floor(GET_MOUSE_YPOS(event)));
			break;
		}
	}
	else if (guistate == PLAYER_GUI_STATE::INVENTORY)
		inventoryGUI->MouseButtonDown(event);
}

void PlayerEntity::MouseButtonUp(ALLEGRO_MOUSE_EVENT& event)
{

}

void PlayerEntity::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	//rotateTo(atan2((event.y - (SCREEN_HEIGHT / 2)) , ((float)event.x - (SCREEN_WIDTH / 2)))+M_PI/2);
}


void PlayerEntity::CharTyped(ALLEGRO_KEYBOARD_EVENT& event)
{
	if (event.keycode == ALLEGRO_KEY_ESCAPE)
	{
		ToggleTyping();
		return;
	}
	if (event.keycode == ALLEGRO_KEY_BACKSPACE)
	{
		if (buf.size())
			buf.pop_back();
		return;
	}
	buf.push_back(event.unichar);
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
static const float PLAYER_SPEED = 0.01f;

void PlayerEntity::PlaceTile(int x, int y)
{
	//printf("PLACING TILE %d:%d\n", x, y);
}

void PlayerEntity::MineTile(int x, int y)
{
	Tile* tile = containingWorld->GetTile(x, y);
	if (tile->IsEmpty())
	{
		GroundTile* gtile = containingWorld->GetGroundTile(x, y);
		SetTarget(gtile);
		GroundTileMiner::Mine();
		return;
	}
	GroundTileMiner::ResetProgress();
	bool success = false;
	switch (tile->GetOptimalToolType())
	{
	case ToolType::PICKAXE:
		success = tile->MineWithTool(pickaxeTool);
		break;
	case ToolType::AXE:
		success = tile->MineWithTool(axeTool);
		break;
	case ToolType::SHOVEL:
		success = tile->MineWithTool(shovelTool);
		break;
	case ToolType::PUMP:
		success = tile->MineWithTool(pumpTool);
		break;
	case ToolType::NONE:
		success = tile->MineWithTool(nullptr);
		break;
	}
	if (success)
	{
		inventory->AddConstItemBundle(tile->GetMiningResult(nullptr));
		containingWorld->RemoveTile(x, y);
	}
}

void PlayerEntity::Tick()
{
	switch (keys_pressed & 0b00001111)
	{
	case 0b0001:
		applyForce(PLAYER_SPEED, 0);
		break;
	case 0b0010:
		applyForce(0, PLAYER_SPEED);
		break;
	case 0b0011:
		applyForce(PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
		break;
	case 0b0100:
		applyForce(-PLAYER_SPEED, 0);
		break;
	case 0b0110:
		applyForce(-PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
		break;
	case 0b1000:
		applyForce(0, -PLAYER_SPEED);
		break;
	case 0b1001:
		applyForce(PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
		break;
	case 0b1100:
		applyForce(-PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
		break;
	}
	Entity::Tick();
}

PlayerEntity::PlayerEntity(World* world, float xpos, float ypos) : Entity(world, xpos, ypos, 1), GUItimer{ 0 }, axeTool{ nullptr }, pickaxeTool{ nullptr }, shovelTool{ nullptr }, pumpTool{ nullptr }, guistate{ PLAYER_GUI_STATE::WORLD }, keys_pressed{ 0b00000000 }, GroundTileMiner(nullptr, nullptr)
{
	inventory = new SimpleItemInventory(36);
	GroundTileMiner::SetTargetItemInventory(inventory);
	inventoryGUI = new SimpleInventoryGUI(inventory);
	hotbarGUI = new SimpleInventoryGUI(inventory);
	for (int i = 0; i < 9; i++)
	{
		hotbarGUI->AddSlotDisplayConfiguration(SlotDisplayConfiguration(i, SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT - 280, 128, 128));
		inventoryGUI->AddSlotDisplayConfiguration(SlotDisplayConfiguration(i, SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT - 280, 128, 128));
		inventoryGUI->AddSlotDisplayConfiguration(SlotDisplayConfiguration(i + 9, SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT / 2 - 192, 128, 128));
		inventoryGUI->AddSlotDisplayConfiguration(SlotDisplayConfiguration(i + 18, SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT / 2 - 64, 128, 128));
		inventoryGUI->AddSlotDisplayConfiguration(SlotDisplayConfiguration(i + 27, SCREEN_WIDTH / 2 - 64 * 9 + 128 * i, SCREEN_HEIGHT / 2 + 64, 128, 128));
	}
	TEXTURE = loaded_bitmaps["tex.entities.player"];
}

PlayerNotification::PlayerNotification(int t, int w, int h)
{
	timer = t;
	content = al_create_bitmap(w, h);
}

void PlayerNotification::Draw(int x, int y, int width, int height, int new_timer)
{
	al_get_blender(&a, &b, &c);
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	al_draw_scaled_bitmap(content, 0, 0, al_get_bitmap_width(content), al_get_bitmap_height(content), x, y, width, height, 0);
	
	al_set_blender(a, b, c);
}

bool PlayerNotification::ShouldBeRemoved(int new_timer)
{
	return timer<new_timer;
}

PlayerNotification* PlayerNotification::MakeTextNotification(std::string txt, int w, int h, int t)
{
	PlayerNotification* p = new PlayerNotification(t, w, h);
	al_set_target_bitmap(p->content);
	al_draw_filled_rectangle(0, 0, w, h, al_map_rgba(200, 200, 20, 170));
	al_draw_multiline_text(loaded_fonts["default"][30], al_map_rgba(0, 0, 0, 255), 10, 10, w - 20, h - 20, 0, txt.c_str());
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
	return p;
}

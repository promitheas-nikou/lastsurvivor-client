#include "PlayerEntity.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "ResourceLoader.h"
#include "SimpleButtonUIComponent.h"
#include "Graphics.h"
#include "World.h"

int a, b, c;

#define GET_MOUSE_XPOS(E) (E.x / 128.f + getXpos() - SCREEN_WIDTH / 256.f)
#define GET_MOUSE_YPOS(E) (E.y / 128.f + getYpos() - SCREEN_HEIGHT / 256.f)

void PlayerEntity::DrawThisGUI()
{
	static ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);
	al_get_blender(&a, &b, &c);
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	al_draw_filled_rectangle(SCREEN_WIDTH/2-250, 50, SCREEN_WIDTH/2+250, 250, al_map_rgba(0, 150, 255, 150));
	float x = GET_MOUSE_XPOS(mouseState);
	float y = GET_MOUSE_YPOS(mouseState);
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 60, 0, "Player:");
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 20), 60, 0, "X: %.3lf", getXpos());
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 + 110), 60, 0, "Y: %.3lf", getYpos());
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 90, 0, "Targeted Tile:");
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 20), 90, 0, "X: %d", (int)floor(x));
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 + 110), 90, 0, "Y: %d", (int)floor(y));
	Tile* targetedTile = containingWorld->GetTile(floor(x), floor(y));
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 150, 0, "Tile:");
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 50), 150, 0, "%s",targetedTile->GetName().c_str());
	if (targetedTile->IsEmpty())
	{
		GroundTile* targetedGroundTile = containingWorld->GetGroundTile(x, y);
		al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 245), 175, al_map_rgba(150, 150, 150, 150));
		al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 245), 145, al_map_rgba(150, 150, 150, 150));
		al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 55 + 190 * 0), 145, al_map_rgba(255, 0, 0, 150));
	}
	else
	{
		al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 245), 175, al_map_rgba(120, 0, 0, 150));
		al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 155, (SCREEN_WIDTH / 2 + 55 + 190 * (targetedTile->GetMiningDamageDone() / (float)targetedTile->GetMiningResistance())), 175, al_map_rgba(255, 0, 0, 150));
		al_draw_filled_rectangle((SCREEN_WIDTH / 2 + 55), 125, (SCREEN_WIDTH / 2 + 245), 145, al_map_rgba(150, 150, 150, 150));
	}
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 230), 120, 0, "Ground Tile:");
	al_draw_textf(loaded_fonts[1][30], al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 50), 120, 0, "%s", containingWorld->GetGroundTile(floor(x),floor(y))->GetName().c_str());
	al_set_blender(a, b, c);
}

void PlayerEntity::Draw()
{
	int x = floor(getXpos() * 128)-64;
	int y = floor(getYpos() * 128)-64;
	al_draw_bitmap(loaded_bitmaps[18], x, y, 0);
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

void PlayerEntity::MouseButtonUp(ALLEGRO_MOUSE_EVENT& event)
{

}

void PlayerEntity::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{

}

static const float DIAG_MOD = 1.4142135623730950488016887242097 / 2;
static const float PLAYER_SPEED = .025f;

void PlayerEntity::PlaceTile(int x, int y)
{
	//printf("PLACING TILE %d:%d\n", x, y);
}

void PlayerEntity::MineTile(int x, int y)
{
	Tile* tile = containingWorld->GetTile(x, y);
	if (tile->IsEmpty())
	{
		return;
	}
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
		Item* miningResult = tile->MineTile();
		containingWorld->RemoveTile(x, y);
	}
}

void PlayerEntity::Tick()
{
	switch (keys_pressed & 0b00001111)
	{
	case 0b0001:
		warpRelative(PLAYER_SPEED, 0);
		break;
	case 0b0010:
		warpRelative(0, PLAYER_SPEED);
		break;
	case 0b0011:
		warpRelative(PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
		break;
	case 0b0100:
		warpRelative(-PLAYER_SPEED, 0);
		break;
	case 0b0110:
		warpRelative(-PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
		break;
	case 0b1000:
		warpRelative(0, -PLAYER_SPEED);
		break;
	case 0b1001:
		warpRelative(PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
		break;
	case 0b1100:
		warpRelative(-PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
		break;
	}
}

PlayerEntity::PlayerEntity(World* world) : Entity(world), axeTool{ nullptr }, pickaxeTool{ nullptr }, shovelTool{ nullptr }, pumpTool{ nullptr }, guistate{ GUI_STATE::WORLD }, keys_pressed{0b00000000}
{}

#include "PlayerEntity.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "ResourceLoader.h"
#include "Graphics.h"
#include "World.h"

int a, b, c;

void PlayerEntity::DrawThisGUI()
{
	al_get_blender(&a, &b, &c);
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	al_draw_filled_rectangle(SCREEN_WIDTH/2-200, 50, SCREEN_WIDTH/2+200, 250, al_map_rgba(0, 150, 255, 150));
	al_draw_textf(loaded_font, al_map_rgba(255, 0, 0, 150), (SCREEN_WIDTH / 2 - 180), 60, 0, "%lf,%lf: %s", getXpos(), getYpos(), containingWorld->GetGroundTile(floor(getXpos()), floor(getYpos()))->GetName().c_str());
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
}

void PlayerEntity::MouseButtonUp(ALLEGRO_MOUSE_EVENT& event)
{
}

void PlayerEntity::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
}

static const float DIAG_MOD = 1.4142135623730950488016887242097 / 2;
static const float PLAYER_SPEED = .025f;

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

PlayerEntity::PlayerEntity(World* world): Entity(world)
{}

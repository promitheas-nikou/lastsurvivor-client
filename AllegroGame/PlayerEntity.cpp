#include "PlayerEntity.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "ResourceLoader.h"
#include "Graphics.h"

int a, b, c;

void PlayerEntity::DrawGUI()
{
	al_get_blender(&a, &b, &c);
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	al_draw_filled_rectangle(SCREEN_WIDTH/2-200, 200, SCREEN_WIDTH/2+200, 450, al_map_rgba(0, 150, 255, 150));
	al_set_blender(a, b, c);
}

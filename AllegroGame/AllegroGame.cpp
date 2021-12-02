#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main()
{
	ALLEGRO_FONT* font = al_load_ttf_font("FONT.ttf", 60, 0);

	while (true)
	{
		al_clear_to_color(al_map_rgb(255, 255, 255));
		al_draw_text(font, al_map_rgb(0, 0, 0), 10, 10, 0, "Hello world!!!\n123123\nthird line");
		al_flip_display();
	}

	al_destroy_font(font);
	al_destroy_display(display);
}
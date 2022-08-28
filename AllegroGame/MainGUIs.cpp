#include "MainGUIs.h"
#include <allegro5/allegro_primitives.h>
#include "Graphics.h"
#include "SimpleTextButtonUIComponent.h"
#include "SimpleTextInputUIComponent.h"
#include "AllegroGame.h"
#include <allegro5/allegro_native_dialog.h>
#include "World.h"

void MainMenuGUI::PreDrawThisGUI()
{
	al_clear_to_color(al_map_rgba(50, 80, 255, 255));
	al_draw_text(loaded_fonts["default"][200], al_map_rgba(255, 255, 255, 255), SCREEN_WIDTH / 2, 250, ALLEGRO_ALIGN_CENTER, "LAST SURVIVOR");
}

void EXIT_GAME();

MainMenuGUI::MainMenuGUI()
{
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100, 300, 100, []() {currentGUI = playMenuGUI;}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "PLAY"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 250, 300, 100, []() {currentGUI = creditsMenuGUI; al_stop_samples(); al_play_sample(loaded_audio_samples["themes.credits"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL); }, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "CREDITS"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 400, 300, 100, []() {EXIT_GAME(); }, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "QUIT"));
}

void PlayMenuGUI::PreDrawThisGUI()
{
	al_clear_to_color(al_map_rgba(50, 80, 255, 255));
	al_draw_text(loaded_fonts["default"][200], al_map_rgba(255, 255, 255, 255), SCREEN_WIDTH / 2, 250, ALLEGRO_ALIGN_CENTER, "LAST SURVIVOR");
}

PlayMenuGUI::PlayMenuGUI()
{
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100, 300, 100, []() {
		currentGUI = worldCreationGUI;
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "CREATE NEW WORLD"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 250, 300, 100, []() {
		ALLEGRO_FILECHOOSER* f = al_create_native_file_dialog("C:/", "SELECT WORLD TO LOAD", "*.zip", ALLEGRO_FILECHOOSER_FILE_MUST_EXIST);
		if (al_show_native_file_dialog(main_display, f)) {
			world = World::LoadWorldFromFile(al_get_native_file_dialog_path(f, 0));
			currentGUI = world->GetPlayer();
			al_stop_samples();
			al_play_sample(loaded_audio_samples["themes.ingame"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
			doWorldTick = true;
		}
		al_destroy_native_file_dialog(f);
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "LOAD WORLD"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 400, 300, 100, []() {
		currentGUI = mainMenuGUI;
		}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "BACK"));
}

void WorldCreationMenuGUI::PreDrawThisGUI()
{
	al_clear_to_color(al_map_rgba(50, 80, 255, 255));
}

WorldCreationMenuGUI::WorldCreationMenuGUI()
{
	SimpleTextInputUIComponent* txtin1 = new SimpleTextInputUIComponent(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 100, 600, 100, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "NEW WORLD NAME: ", "", ALLEGRO_ALIGN_LEFT);
	UIcomponents.push_back(txtin1);
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 250, 300, 100, [txtin1]() {
		world = World::CreateNewWorld(txtin1->GetTextBuffer());
		currentGUI = world->GetPlayer();
		al_stop_samples();
		al_play_sample(loaded_audio_samples["themes.ingame"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
		doWorldTick = true;
		
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "CREATE WORLD"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 400, 300, 100, []() {
		currentGUI = playMenuGUI;
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "CANCEL"));
}

void CreditsMenuGUI::PreDrawThisGUI()
{
	al_clear_to_color(al_map_rgba(50, 80, 255, 255));
	al_draw_text(loaded_fonts["default"][50],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 100, ALLEGRO_ALIGN_CENTER, "LAST SURVIVOR");
	al_draw_text(loaded_fonts["default"][40],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 160, ALLEGRO_ALIGN_CENTER, "THE TEAM:");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), 100, 300, ALLEGRO_ALIGN_LEFT, "LEAD (AND CURRENTLY ONLY) DEVELOPPER:");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 300, ALLEGRO_ALIGN_CENTER, "PROMITHEAS NIKOU");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), 100, 440, ALLEGRO_ALIGN_LEFT, "TEXTURES AND LEVEL DESIGN:");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 440, ALLEGRO_ALIGN_CENTER, "GIORGOS MPOTTAS");
	//al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), 100, 480, ALLEGRO_ALIGN_LEFT, "TEXTURES AND LEVEL DESIGN:");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 480, ALLEGRO_ALIGN_CENTER, "TAXIARCHIS SENEKIS");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), 100, 620, ALLEGRO_ALIGN_LEFT, "ORIGINAL MUSIC:");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 620, ALLEGRO_ALIGN_CENTER, "THEOFILOS MYSTIDIS");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), 100, 760, ALLEGRO_ALIGN_LEFT, "SPECIAL THANKS TO:");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 760, ALLEGRO_ALIGN_CENTER, "APOSTOLOS ADAMOS");
}

CreditsMenuGUI::CreditsMenuGUI()
{
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 100, 300, 100, []() {
		currentGUI = mainMenuGUI; al_stop_samples(); al_play_sample(loaded_audio_samples["themes.menu"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "BACK"));
}


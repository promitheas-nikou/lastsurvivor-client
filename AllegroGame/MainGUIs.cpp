#include "MainGUIs.h"
#include <allegro5/allegro_primitives.h>
#include "Graphics.h"
#include "SimpleTextButtonUIComponent.h"
#include "SimpleTextInputUIComponent.h"
#include "SimpleNumberInputUIComponent.h"
#include "SimpleToggleTextButtonUIComponent.h"
#include "AllegroGame.h"
#include <allegro5/allegro_native_dialog.h>
#include "World.h"
#include "Config.h"

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
	SimpleTextInputUIComponent* namein = new SimpleTextInputUIComponent(SCREEN_WIDTH / 2 - 600, 200, 1200, 100, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "NEW WORLD NAME: \"", "", "\"", ALLEGRO_ALIGN_LEFT);
	SimpleNumberInputUIComponent* seedin = new SimpleNumberInputUIComponent(SCREEN_WIDTH / 2 - 600, 350, 1200, 100, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "WORLD SEED (DECIMAL NUMBER; LEAVE EMPTY FOR RANDOM): [", "", "]", ALLEGRO_ALIGN_LEFT);
	SimpleToggleTextButtonUIComponent* isDynamicTB = new SimpleToggleTextButtonUIComponent(SCREEN_WIDTH / 2 - 600, 500, 1200, 100, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "DO DYNAMIC WORLD GENERATION", true);

	SimpleNumberInputUIComponent* mincx = new SimpleNumberInputUIComponent(SCREEN_WIDTH / 2 - 600, 650, 550, 80, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "MIN CHUNK X: [", "", "]", ALLEGRO_ALIGN_LEFT);
	SimpleNumberInputUIComponent* maxcx = new SimpleNumberInputUIComponent(SCREEN_WIDTH / 2 + 50, 650, 550, 80, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "MAX CHUNK X: [", "", "]", ALLEGRO_ALIGN_LEFT);
	SimpleNumberInputUIComponent* mincy = new SimpleNumberInputUIComponent(SCREEN_WIDTH / 2 - 600, 750, 550, 80, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "MIN CHUNK Y: [", "", "]", ALLEGRO_ALIGN_LEFT);
	SimpleNumberInputUIComponent* maxcy = new SimpleNumberInputUIComponent(SCREEN_WIDTH / 2 + 50, 750, 550, 80, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "MAX CHUNK Y: [", "", "]", ALLEGRO_ALIGN_LEFT);

	UIcomponents.push_back(namein);
	UIcomponents.push_back(seedin);
	UIcomponents.push_back(isDynamicTB);
	UIcomponents.push_back(mincx);
	UIcomponents.push_back(maxcx);
	UIcomponents.push_back(mincy);
	UIcomponents.push_back(maxcy);

	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT - 250, 300, 100, [namein,seedin,isDynamicTB,mincx,mincy,maxcx,maxcy]() {
		if (seedin->GetTextBuffer().empty())
		{
			srand((unsigned int)time(NULL));
		}
		else
		{
			srand(seedin->GetInputNumber());
		}
		for (int i = 0; i < 10; i++)
			rand();
		uint64_t seed = abs(rand() * rand() * rand() * rand() * rand());
		if(isDynamicTB->GetIsToggledOn())
			world = World::CreateNewWorld(namein->GetTextBuffer(), seed, [](int,int,int,int) {});
		else
		{
			bool isError = false;
			if (mincx->GetTextBuffer().empty())
			{
				mincx->SetAlert("YOU MUST ENTER A VALUE", gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR);
				isError = true;
			}
			if (mincy->GetTextBuffer().empty())
			{
				mincy->SetAlert("YOU MUST ENTER A VALUE", gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR);
				isError = true;
			}
			if (maxcx->GetTextBuffer().empty())
			{
				maxcx->SetAlert("YOU MUST ENTER A VALUE", gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR);
				isError = true;
			}
			if (maxcy->GetTextBuffer().empty())
			{
				maxcy->SetAlert("YOU MUST ENTER A VALUE", gameconfig::SOLID_BACKGROUND_COLOR_0, gameconfig::SOLID_TEXT_COLOR_ERROR);
				isError = true;
			}
			if (isError)
				return;

			al_clear_to_color(al_map_rgba(50, 80, 255, 255));
			al_draw_filled_rectangle(SCREEN_WIDTH / 4 - 10, SCREEN_HEIGHT / 2 - 110, 3 * SCREEN_WIDTH / 4 + 10, SCREEN_HEIGHT / 2 + 10, al_map_rgba(255, 255, 255, 255));
			al_flip_display();
			//TODO: DELETE THIS BODGE
			al_clear_to_color(al_map_rgba(50, 80, 255, 255));
			al_draw_filled_rectangle(SCREEN_WIDTH / 4 - 10, SCREEN_HEIGHT / 2 - 110, 3 * SCREEN_WIDTH / 4 + 10, SCREEN_HEIGHT / 2 + 10, al_map_rgba(255, 255, 255, 255));
			al_flip_display();
			al_clear_to_color(al_map_rgba(50, 80, 255, 255));
			al_draw_filled_rectangle(SCREEN_WIDTH / 4 - 10, SCREEN_HEIGHT / 2 - 110, 3 * SCREEN_WIDTH / 4 + 10, SCREEN_HEIGHT / 2 + 10, al_map_rgba(255, 255, 255, 255));
			al_flip_display();
			world = World::CreateNewFixedSizeWorld(namein->GetTextBuffer(), seed, mincx->GetInputNumber(), mincy->GetInputNumber(), maxcx->GetInputNumber(), maxcy->GetInputNumber(), [](int cx, int cy, int c, int t) {
				static double lastDraw = al_get_time();
				float progress = ((float)c) / t;
				al_draw_filled_rectangle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 100, SCREEN_WIDTH / 4 + SCREEN_WIDTH * (progress / 2), SCREEN_HEIGHT / 2, al_map_rgba(255, 255, 255, 255));
				al_draw_filled_rectangle(SCREEN_WIDTH / 4 + SCREEN_WIDTH * (progress / 2), SCREEN_HEIGHT / 2 - 100, 3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, al_map_rgba(50, 80, 255, 255));
				al_draw_filled_rectangle(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 100, 3 * SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 + 140,al_map_rgba(50,80,255,255));
				al_draw_textf(loaded_fonts["default"][30], al_map_rgba(255, 255, 255, 255), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 100, ALLEGRO_ALIGN_LEFT, "[%d%% DONE] Generating Chunk (%d,%d)...", (int)(progress * 100), cx, cy);
				al_flip_display();
			});
		}
		currentGUI = world->GetPlayer();
		al_stop_samples();
		al_play_sample(loaded_audio_samples["themes.ingame"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
		doWorldTick = true;
		
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "CREATE WORLD"));
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT - 250, 300, 100, []() {
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
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 800, ALLEGRO_ALIGN_CENTER, "MARKELLA SENEKH");
	al_draw_text(loaded_fonts["default"][30],al_map_rgba(255,255,255,255), SCREEN_WIDTH/2, 840, ALLEGRO_ALIGN_CENTER, "LAZAROS TZHMKAS");
}

CreditsMenuGUI::CreditsMenuGUI()
{
	UIcomponents.push_back(new SimpleTextButtonUIComponent(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 100, 300, 100, []() {
		currentGUI = mainMenuGUI; al_stop_samples(); al_play_sample(loaded_audio_samples["themes.menu"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
	}, al_map_rgba(255, 255, 255, 255), al_map_rgba(0, 0, 0, 255), "BACK"));
}


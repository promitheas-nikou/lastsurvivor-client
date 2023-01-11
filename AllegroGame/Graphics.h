#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstdio>

extern ALLEGRO_DISPLAY* main_display;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void init_graphics();

void init_sound();

void init_window();

void config_window();

void destroy_graphics();


extern ALLEGRO_EVENT NEXT_EVENT;
bool GetNextEvent();
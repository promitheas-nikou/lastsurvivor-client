#pragma once
#define ALLEGRO_UNSTABLE
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
class World;
class GUI;

extern const float TPS;

extern GUI* playMenuGUI;
extern GUI* mainMenuGUI;
extern GUI* currentGUI;
extern GUI* creditsMenuGUI;
extern GUI* worldCreationGUI;
extern World* world;
extern bool doWorldTick;


extern ALLEGRO_MUTEX* worldMutex;
extern ALLEGRO_THREAD* worldTickerThread;

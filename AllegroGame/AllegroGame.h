#pragma once
#include "MainGUIs.h"
class World;

extern GUI* playMenuGUI;
extern GUI* mainMenuGUI;
extern GUI* currentGUI;
extern GUI* creditsMenuGUI;
extern GUI* worldCreationGUI;
extern World* world;
extern bool doWorldTick;


extern ALLEGRO_MUTEX* worldMutex;
extern ALLEGRO_THREAD* worldTickerThread;

#pragma once
#include "GUI.h"

class MainMenuGUI :
    public GUI
{
public:
    virtual void PreDrawThisGUI() final;
    MainMenuGUI();
};

class PlayMenuGUI :
    public GUI
{
public:
    virtual void PreDrawThisGUI() final;
    PlayMenuGUI();
};

class WorldCreationMenuGUI :
    public GUI
{
public:
    virtual void PreDrawThisGUI() final;
    WorldCreationMenuGUI();
};

class CreditsMenuGUI :
    public GUI
{
public:
    virtual void PreDrawThisGUI() final;
    CreditsMenuGUI();
};

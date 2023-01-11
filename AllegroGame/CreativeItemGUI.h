#pragma once
#include "GUI.h"
#include "Item.h"
#include "Graphics.h"

class PlayerEntity;

class CreativeItemGUI :
    public GUI
{
private:
    std::vector<const Item*> itemsList;
    int pageHeight;
    int scroll;
    PlayerEntity* player;

    void DrawItem(const Item* item, int x, int y, int tw, int th, int rw, int rh);

public:

    void PreDrawThisGUI() override;
    void PostDrawThisGUI() override;

    virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) override;
    virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) override;

    void SetCurrentPlayer(PlayerEntity* p);
    void SetItemsList(std::unordered_map<std::string, Item*> i);

    CreativeItemGUI(PlayerEntity* p, int pageHeight = (SCREEN_HEIGHT - 362) / 148);

    ~CreativeItemGUI() = default;
};


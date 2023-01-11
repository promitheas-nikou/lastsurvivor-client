#pragma once
#include "GUI.h"

#include "QuestCollection.h"

class QuestGUI :
    public GUI
{
public:
private:

    const int WIDTH = 128;
    const int HEIGHT = 128;

    void QuestDrawIcon(Quest* q, int curx, int cury) const;
    void QuestDrawHover(Quest* q, int curx, int cury) const;
    void QuestDrawFull(Quest* q) const;
    bool QuestContains(Quest* q, int x, int y) const;
    QuestCollection* questCollection;

    mutable Quest* curQuest;
    mutable Quest* curQuestHover;
    mutable int curx;
    mutable int cury;
public:

    virtual void PreDrawThisGUI() override;
    virtual void PostDrawThisGUI() final;

    virtual bool ClickRightDown(int xRel, int yRel) override;
    virtual bool ClickLeftDown(int xRel, int yRel) override;

    virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& event) override;

    virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event);

    QuestGUI(QuestCollection* collection);

    virtual ~QuestGUI() = default;

    friend class PlayerEntity;
};


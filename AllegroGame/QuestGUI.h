#pragma once
#include "GUI.h"

#include "QuestCollection.h"

class QuestGUI :
    public GUI
{
public:
    
    class QuestDisplayConfiguration {
    public:
        int x;
        int y;
        int width;
        int height;
        int id;
        Quest* quest;
        void DrawIcon(int curx, int cury) const;
        void DrawHover(int curx, int cury) const;
        void DrawFull() const;
        bool Contains(int x, int y) const;
        QuestDisplayConfiguration(Quest* q);
    };
private:
    QuestCollection* questCollection;
    std::vector<QuestDisplayConfiguration*> displayConfig;
    std::map<Quest*, QuestDisplayConfiguration*> questLink;

    mutable int curx;
    mutable int cury;
    mutable QuestDisplayConfiguration* curQuest;
    mutable QuestDisplayConfiguration* curQuestHover;

    void AddQuestDisplayConfiguration(QuestDisplayConfiguration* config);
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


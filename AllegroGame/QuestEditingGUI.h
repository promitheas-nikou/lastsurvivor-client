#pragma once
#include "Config.h"
#include "GUI.h"
#include "Quest.h"
#include "Graphics.h"
#include "SimpleTextInputUIComponent.h"
#include "SimpleTextButtonUIComponent.h"
#include "SimpleToggleTextButtonUIComponent.h"
#include "SimpleNumberInputUIComponent.h"
class PlayerEntity;

class QuestEditingGUI :
    public GUI
{
private:
    QuestCollection* questCollection;
    int pageHeight;
    int scroll;
    PlayerEntity* player;

    class NewQuestCreationGUI:
        public GUI
    {
    private:
        QuestEditingGUI* parent;
        SimpleTextInputUIComponent* idTextInput;
        SimpleTextInputUIComponent* nameTextInput;
        SimpleTextInputUIComponent* iconIDTextInput;
        SimpleTextButtonUIComponent* doneButton;
        SimpleTextButtonUIComponent* cancelButton;
    public:
        void PreDrawThisGUI() final;
        bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;
        NewQuestCreationGUI(QuestEditingGUI* par);
    };

    NewQuestCreationGUI* questCreationGUI;

    class ExistingQuestEditingGUI:
        public GUI
    {
    private:

        class QuestRequirementEditingGUI :
            public GUI
        {
        private:
            class TileQuestRequirementEditingGUI :
                public GUI
            {
            private:
                class NewTileQuestRequirementCreationGUI :
                    public GUI
                {
                private:
                    TileQuestRequirementEditingGUI* parent;

                    SimpleTextInputUIComponent* tileIDTextInput;
                    SimpleNumberInputUIComponent* tileCountNumberInput;

                    SimpleTextButtonUIComponent* cancelButton;
                    SimpleTextButtonUIComponent* doneButton;
                public:
                    bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;
                    NewTileQuestRequirementCreationGUI(TileQuestRequirementEditingGUI* par);
                };
                QuestRequirementEditingGUI* parent;
                NewTileQuestRequirementCreationGUI* creationGUI;
                int pageHeight;
                int scroll;

                SimpleTextButtonUIComponent* cancelButton;
                SimpleTextButtonUIComponent* newButton;

                void DrawRequirementIcon(const Quest::TileMineRequirement& quest, int x, int y, int lw, int lh);
                
            public:
                void PreDrawThisGUI() final;

                bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) final;
                bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;

                TileQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight = (SCREEN_HEIGHT - 148 * 3 - gameconfig::GUI_DEFAULT_LINE_HEIGHT) / 148);
            };

            class GroundTileQuestRequirementEditingGUI :
                public GUI
            {
            private:
                class NewGroundTileQuestRequirementCreationGUI :
                    public GUI
                {
                private:
                    GroundTileQuestRequirementEditingGUI* parent;

                    SimpleTextInputUIComponent* gtileIDTextInput;
                    SimpleNumberInputUIComponent* gtileCountNumberInput;

                    SimpleTextButtonUIComponent* cancelButton;
                    SimpleTextButtonUIComponent* doneButton;
                public:
                    bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;
                    NewGroundTileQuestRequirementCreationGUI(GroundTileQuestRequirementEditingGUI* par);
                };
                QuestRequirementEditingGUI* parent;
                NewGroundTileQuestRequirementCreationGUI* creationGUI;
                int pageHeight;
                int scroll;

                SimpleTextButtonUIComponent* cancelButton;
                SimpleTextButtonUIComponent* newButton;

                void DrawRequirementIcon(const Quest::GroundTileMineRequirement& quest, int x, int y, int lw, int lh);

            public:
                void PreDrawThisGUI() final;

                bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) final;
                bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;

                GroundTileQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight = (SCREEN_HEIGHT - 148 * 3 - gameconfig::GUI_DEFAULT_LINE_HEIGHT) / 148);
            };

            class EntityKillQuestRequirementEditingGUI :
                public GUI
            {
            private:
                class NewEntityKillQuestRequirementCreationGUI :
                    public GUI
                {
                private:
                    EntityKillQuestRequirementEditingGUI* parent;

                    SimpleTextInputUIComponent* entityIDTextInput;
                    SimpleNumberInputUIComponent* killCountNumberInput;

                    SimpleTextButtonUIComponent* cancelButton;
                    SimpleTextButtonUIComponent* doneButton;
                public:
                    NewEntityKillQuestRequirementCreationGUI(EntityKillQuestRequirementEditingGUI* par);
                    bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;
                };
                QuestRequirementEditingGUI* parent;
                NewEntityKillQuestRequirementCreationGUI* creationGUI;
                int pageHeight;
                int scroll;

                SimpleTextButtonUIComponent* cancelButton;
                SimpleTextButtonUIComponent* newButton;

                void DrawRequirementIcon(const Quest::EntityKillRequirement& quest, int x, int y, int lw, int lh);

            public:
                void PreDrawThisGUI() final;

                bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) final;
                bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;

                EntityKillQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight = (SCREEN_HEIGHT - 148 * 3 - gameconfig::GUI_DEFAULT_LINE_HEIGHT) / 148);
            };
            class QuestCompletionQuestRequirementEditingGUI :
                public GUI
            {
            private:
                class NewQuestCompletionQuestRequirementCreationGUI :
                    public GUI
                {
                private:
                    QuestCompletionQuestRequirementEditingGUI* parent;

                    SimpleTextInputUIComponent* questIDTextInput;

                    SimpleTextButtonUIComponent* cancelButton;
                    SimpleTextButtonUIComponent* doneButton;
                public:
                    bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;
                    NewQuestCompletionQuestRequirementCreationGUI(QuestCompletionQuestRequirementEditingGUI* par);
                };
                QuestRequirementEditingGUI* parent;
                NewQuestCompletionQuestRequirementCreationGUI* creationGUI;
                int pageHeight;
                int scroll;

                SimpleTextButtonUIComponent* cancelButton;
                SimpleTextButtonUIComponent* newButton;

                void DrawRequirementIcon(const Quest::QuestCompletionRequirement& quest, int x, int y, int lw, int lh);

            public:
                void PreDrawThisGUI() final;

                bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) final;
                bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;

                QuestCompletionQuestRequirementEditingGUI(QuestRequirementEditingGUI* par, int pageHeight = (SCREEN_HEIGHT - 148 * 3 - gameconfig::GUI_DEFAULT_LINE_HEIGHT) / 148);
            };

            ExistingQuestEditingGUI* parent;
            Quest* quest;
            TileQuestRequirementEditingGUI* tileRequirementEditingGUI;
            GroundTileQuestRequirementEditingGUI* gtileRequirementEditingGUI;
            EntityKillQuestRequirementEditingGUI* killRequirementEditingGUI;
            QuestCompletionQuestRequirementEditingGUI* questRequirementEditingGUI;

            SimpleTextButtonUIComponent* tileRequirementButton;
            SimpleTextButtonUIComponent* gtileRequirementButton;
            SimpleTextButtonUIComponent* killRequirementButton;
            SimpleTextButtonUIComponent* questRequirementButton;
            SimpleTextButtonUIComponent* backButton;

        public:
            void PreDrawThisGUI() final;

            QuestRequirementEditingGUI(ExistingQuestEditingGUI* par);

            void SetQuest(Quest* q);
        };

        QuestEditingGUI* parent;
        int questIndex;
        SimpleTextInputUIComponent* idTextInput;
        SimpleTextInputUIComponent* nameTextInput;
        SimpleTextInputUIComponent* iconIDTextInput;

        SimpleToggleTextButtonUIComponent* completedToggleButton;
        SimpleToggleTextButtonUIComponent* unlockedToggleButton;

        SimpleNumberInputUIComponent* xNumInput;
        SimpleNumberInputUIComponent* yNumInput;


        SimpleTextButtonUIComponent* editQuestRequirementsButton;

        SimpleTextButtonUIComponent* doneButton;
        SimpleTextButtonUIComponent* cancelButton;

        QuestRequirementEditingGUI* requiremenentEditingGUI;
    public:
        void PreDrawThisGUI() final;

        ExistingQuestEditingGUI(QuestEditingGUI* par);

        void SetQuestIndex(int i);
    };

    ExistingQuestEditingGUI* questEditingGUI;

    void DrawQuestIcon(const Quest* quest, int x, int y, int tw, int th, int rw, int rh);

    friend NewQuestCreationGUI;
public:

    void PreDrawThisGUI() override;
    void PostDrawThisGUI() override;

    virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) final;
    virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) final;

    void SetCurrentPlayer(PlayerEntity* p);
    void SetQuestCollection(QuestCollection* col);
    QuestCollection* GetQuestCollection() const;

    QuestEditingGUI(PlayerEntity* p, int pageHeight = (SCREEN_HEIGHT - 362) / 148);

    ~QuestEditingGUI() = default;
};


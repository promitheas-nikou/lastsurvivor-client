#pragma once
#include "GUI.h"
#include "ResourceLoader.h"
#include "Recipe.h"
#include "Graphics.h"
#include <allegro5/allegro_primitives.h>
#include "SimpleItemInventory.h"
#include "ItemIndex.h"
#include <functional>

class SimpleCraftingGUI :
    public GUI
{
private:
    std::function<void(const CraftingRecipe*, int)> recipeCraftedCallback;

    class SingleRecipeExecutionGUI :
        public GUI
    {   
    private:
        SimpleCraftingGUI* parent;
        const CraftingRecipe* recipe;
        ItemInventory* inventory;
        ItemIndex index;
        ALLEGRO_BITMAP* b1;
        ALLEGRO_BITMAP* b2;
        ALLEGRO_BITMAP* b3;
    public:
        void SetRecipe(const CraftingRecipe* r);
        const CraftingRecipe* GetRecipe() const;
        void SetInventory(ItemInventory* i);
        ItemInventory* GetInventory() const;

        void PreDrawThisGUI() override;
        void PostDrawThisGUI() override;

        SingleRecipeExecutionGUI(SimpleCraftingGUI* parent);

        virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) override;

        virtual ~SingleRecipeExecutionGUI();

    };

    SingleRecipeExecutionGUI* recipeGUI;

    std::vector<const CraftingRecipe*> recipes;

    int pageHeight;
    int scroll;

    void DrawRecipe(const CraftingRecipe* recipe, int x, int y, int tw, int th, int rw, int rh);

public:

    void PreDrawThisGUI() override;
    void PostDrawThisGUI() override;

    virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) override;
    virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) override;
    virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& event) override;

    void SetRecipeCallbackFunction(std::function<void(const CraftingRecipe*, int)> callback);

    void SetInventory(ItemInventory* inventory);
    ItemInventory* GetInventory() const;

    void SetRecipeList(std::unordered_map<std::string, const CraftingRecipe*>& r);

    SimpleCraftingGUI();
};


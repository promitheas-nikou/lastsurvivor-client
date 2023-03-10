#pragma once
#include "GUI.h"
#include "Recipe.h"

class RecipeListGUI :
    public GUI
{
protected:

    void DrawRecipe(const CraftingRecipe* recipe, int x, int y, int w, int h);

public:

    virtual void SetRecipeList(std::unordered_map<std::string, const CraftingRecipe*>& recipes) = 0;
};


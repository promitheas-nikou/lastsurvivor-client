#pragma once
#include "RecipeListGUI.h"
class SimpleRecipeListGUI :
    public RecipeListGUI
{
private:

    std::vector<const Recipe*> recipes;

    int X,Y,W,H;
    int scroll;
    int pageHeight;

public:

    virtual void SetRecipeList(std::unordered_map<std::string, const Recipe*>& r) override;

    virtual void DrawThisGUI() override;

    virtual void MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) override;

    SimpleRecipeListGUI(int x, int y, int w, int h);

    virtual ~SimpleRecipeListGUI() = default;

};


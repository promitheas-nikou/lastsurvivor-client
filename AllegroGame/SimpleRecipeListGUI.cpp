#include "SimpleRecipeListGUI.h"
#include <algorithm>

void SimpleRecipeListGUI::SetRecipeList(std::unordered_map<std::string, const Recipe*>& r)
{
	recipes.clear();
	for (const std::pair<std::string, const Recipe*>& p : r)
		recipes.push_back(p.second);
}

void SimpleRecipeListGUI::PreDrawThisGUI()
{
	int y = Y;
	for (int i=scroll;i<std::min((int)recipes.size(),scroll+pageHeight);i++)
	{
		DrawRecipe(recipes[i], X, y, W, H);
		y += H + 16;
	}
}

void SimpleRecipeListGUI::PostDrawThisGUI()
{

}

bool SimpleRecipeListGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	if(event.dz)
		scroll += std::max(0,std::min((event.dz > 0) ? pageHeight : -pageHeight,(int)recipes.size()-pageHeight));
	return true;
}

SimpleRecipeListGUI::SimpleRecipeListGUI(int x, int y, int w, int h) : X{ x }, Y{ y }, W{ w }, H{ h }, pageHeight{ 10 }, scroll{0}
{}

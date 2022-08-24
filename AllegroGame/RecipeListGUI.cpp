#include "RecipeListGUI.h"
#include "ResourceLoader.h"

void RecipeListGUI::DrawRecipe(const CraftingRecipe* recipe, int x, int y, int w, int h)
{
	const ItemBundle* in = recipe->GetInputItems();
	int a = in->GetSize();
	const ItemBundle* out = recipe->GetOutputItems();
	int b = out->GetSize();
	for (int i = 0; i < a; i++)
		in->GetItem(i)->Draw(x + i * (w + 10), y, w, h);
	al_draw_scaled_bitmap(loaded_bitmaps["tex.gui.crafting_arrow"], 0, 0, 128, 128, x + a * (w + 10), y, w, h, 0);
	for (int i = 0; i < b; i++)
		out->GetItem(i)->Draw(x + a * (w + 10) + (i + 1) * (w + 10), y, w, h);
}

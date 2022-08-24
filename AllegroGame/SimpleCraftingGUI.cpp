#include "SimpleCraftingGUI.h"
#include "Config.h"
#include "TextUtils.h"
#include "SimpleButtonUIComponent.h"
#include <algorithm>

void SimpleCraftingGUI::DrawRecipe(const CraftingRecipe* recipe, int x, int y, int tw, int th, int rw, int rh)
{
	al_draw_filled_rectangle(x, y, x + tw, y + th, gameconfig::SOLID_BACKGROUND_COLOR_0);
	const ItemBundle* in = recipe->GetInputItems();
	int a = in->GetSize();
	const ItemBundle* out = recipe->GetOutputItems();
	int b = out->GetSize();
	for (int i = 0; i < a; i++)
		in->GetItem(i)->Draw(x + i * (rw + 4), y, rw, rh);
	al_draw_scaled_bitmap(loaded_bitmaps["tex.gui.crafting_arrow"], 0, 0, 128, 128, x+tw/2-64, y, rw, rh, 0);
	for (int i = 0; i < b; i++)
		out->GetItem(i)->Draw(x+tw/2+68 + i * (rw + 4), y, rw, rh);
}

void SimpleCraftingGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	const char* header = "CRAFTING MENU";
	al_draw_filled_rectangle(132, 132, SCREEN_WIDTH - 132, 200, gameconfig::SOLID_BACKGROUND_COLOR_0);
	TextUtils::DrawCenteredText(loaded_fonts["default"][30],SCREEN_WIDTH/2,132,header,gameconfig::SOLID_TEXT_COLOR_NORMAL);
	for (int i = 0; i < std::min((unsigned long long) pageHeight,recipes.size()-scroll); i++)
		DrawRecipe(recipes[i+scroll], 148, 214 + i * 148, SCREEN_WIDTH - 296, 128, 128, 128);
}

void SimpleCraftingGUI::PostDrawThisGUI()
{
}

bool SimpleCraftingGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll >= recipes.size() - pageHeight)
		scroll = recipes.size()-pageHeight-1;
	return true;
}

bool SimpleCraftingGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if (event.button != 1)
		return true;
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= 214) && (event.y <= SCREEN_HEIGHT - 128))
	{
		int ind = ((event.y - 214) / 148) + scroll;
		if(ind<recipes.size())
			recipeGUI->SetRecipe(recipes[ind]);
		activeSubGUI = recipeGUI;
	}
	return true;
}

bool SimpleCraftingGUI::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
	if (activeSubGUI == nullptr)
		return false;
	if(event.keycode==ALLEGRO_KEY_ESCAPE)
		activeSubGUI = nullptr;
	return true;
}

void SimpleCraftingGUI::SetInventory(ItemInventory* inventory)
{
	recipeGUI->SetInventory(inventory);
}

ItemInventory* SimpleCraftingGUI::GetInventory() const
{
	return recipeGUI->GetInventory();
}

void SimpleCraftingGUI::SetRecipeList(std::unordered_map<std::string, const CraftingRecipe*>& r)
{
	recipes.clear();
	for (const std::pair<std::string, const CraftingRecipe*>& p: r)
		recipes.push_back(p.second);
}

void SimpleCraftingGUI::SetRecipeCallbackFunction(std::function<void(const CraftingRecipe*, int)> callback)
{
	recipeCraftedCallback = callback;
}

SimpleCraftingGUI::SimpleCraftingGUI() : GUI(), scroll{ 0 }, pageHeight{ (SCREEN_HEIGHT - 362) / 148 }
{
	recipeGUI = new SingleRecipeExecutionGUI(this);
}

void SimpleCraftingGUI::SingleRecipeExecutionGUI::SetRecipe(const CraftingRecipe* r)
{
	recipe = r;
	if(inventory!=nullptr)
		index = ItemIndex(inventory);
}

const CraftingRecipe* SimpleCraftingGUI::SingleRecipeExecutionGUI::GetRecipe() const
{
	return recipe;
}

void SimpleCraftingGUI::SingleRecipeExecutionGUI::SetInventory(ItemInventory* i)
{
	inventory = i;
}

ItemInventory* SimpleCraftingGUI::SingleRecipeExecutionGUI::GetInventory() const
{
	return inventory;
}

void SimpleCraftingGUI::SingleRecipeExecutionGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(300, 100, SCREEN_WIDTH - 300, SCREEN_HEIGHT - 100, gameconfig::SOLID_BACKGROUND_COLOR_2);
	al_draw_filled_rectangle(340, 140, SCREEN_WIDTH-340, SCREEN_HEIGHT-140, gameconfig::SOLID_BACKGROUND_COLOR_1);
	al_draw_filled_rectangle(360, 220, SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT - 340, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_filled_rectangle(SCREEN_WIDTH / 2 + 20, 220, SCREEN_WIDTH - 360, SCREEN_HEIGHT - 340, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_filled_rectangle(360, 160, SCREEN_WIDTH / 2 - 20, 200, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_filled_rectangle(SCREEN_WIDTH / 2 + 20, 160, SCREEN_WIDTH - 360, 200, gameconfig::SOLID_BACKGROUND_COLOR_0);
	TextUtils::DrawCenteredText(loaded_fonts["default"][35], (SCREEN_WIDTH / 4) + 170, 160, "INGREDIENTS", gameconfig::SOLID_TEXT_COLOR_NORMAL);
	TextUtils::DrawCenteredText(loaded_fonts["default"][35], (3*SCREEN_WIDTH / 4) - 170, 160, "RESULT", gameconfig::SOLID_TEXT_COLOR_NORMAL);
	const ItemBundle* in = recipe->GetInputItems();
	const ItemBundle* out = recipe->GetOutputItems();
	for (int i = 0; i < in->GetSize(); i++)
	{
		in->GetItem(i)->DrawWithText(380, 240 + i * 140, 128, 128);
		//al_draw_textf(loaded_fonts["default"][35] gameconfig::)
	}
	for (int i = 0; i < out->GetSize(); i++)
		out->GetItem(i)->DrawWithText(SCREEN_WIDTH/2+40, 240+i*140, 128, 128);
}

void SimpleCraftingGUI::SingleRecipeExecutionGUI::PostDrawThisGUI()
{
}

SimpleCraftingGUI::SingleRecipeExecutionGUI::SingleRecipeExecutionGUI(SimpleCraftingGUI* par): parent{par}
{
	ALLEGRO_BITMAP* b1 = al_create_bitmap(384, 128);
	ALLEGRO_BITMAP* b2 = al_create_bitmap(384, 128);
	ALLEGRO_BITMAP* b3 = al_create_bitmap(384, 128);
	al_set_target_bitmap(b1);
	al_draw_filled_rectangle(0, 0, 384, 128, gameconfig::SOLID_BACKGROUND_COLOR_0);
	TextUtils::DrawCenteredText(loaded_fonts["default"][30], 192, 48, "CRAFT ONE",gameconfig::SOLID_TEXT_COLOR_NORMAL);
	al_set_target_bitmap(b2);
	al_draw_filled_rectangle(0, 0, 384, 128, gameconfig::SOLID_BACKGROUND_COLOR_0);
	TextUtils::DrawCenteredText(loaded_fonts["default"][30], 192, 48, "CRAFT FIVE",gameconfig::SOLID_TEXT_COLOR_NORMAL);
	al_set_target_bitmap(b3);
	al_draw_filled_rectangle(0, 0, 384, 128, gameconfig::SOLID_BACKGROUND_COLOR_0);
	TextUtils::DrawCenteredText(loaded_fonts["default"][30], 192, 48, "CRAFT MAX",gameconfig::SOLID_TEXT_COLOR_NORMAL);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
	GUI::UIcomponents.push_back(new SimpleButtonUIComponent(360, SCREEN_HEIGHT-300, 384, 128, b1, [&]() {
		recipe->PerformOnInventory(inventory);
		parent->recipeCraftedCallback(recipe, 1);
	}));
	GUI::UIcomponents.push_back(new SimpleButtonUIComponent(SCREEN_WIDTH/2-160, SCREEN_HEIGHT - 300, 384, 128, b2, [&]() {
		recipe->PerformOnInventory(inventory);
		recipe->PerformOnInventory(inventory);
		recipe->PerformOnInventory(inventory);
		recipe->PerformOnInventory(inventory);
		recipe->PerformOnInventory(inventory);
		parent->recipeCraftedCallback(recipe, 5);
	}));
	GUI::UIcomponents.push_back(new SimpleButtonUIComponent(SCREEN_WIDTH-744, SCREEN_HEIGHT - 300, 384, 128, b3, [&]() {
		int n = recipe->CheckTimesPerformOnInventory(inventory);
		for (int i = 0; i < n; i++)
			recipe->PerformOnInventory(inventory);
		parent->recipeCraftedCallback(recipe, n);
	}));

}

bool SimpleCraftingGUI::SingleRecipeExecutionGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if (event.button != 1)
		return true;
	return true;
}

SimpleCraftingGUI::SingleRecipeExecutionGUI::~SingleRecipeExecutionGUI()
{
	al_destroy_bitmap(b1);
	al_destroy_bitmap(b2);
	al_destroy_bitmap(b3);
}

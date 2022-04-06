#pragma once
#include "Entity.h"
#include "InventoryGUI.h"
#include "GroundTileMiner.h"
#include "ItemInventory.h"
#include "SimpleInventoryGUI.h"
#include "RecipeListGUI.h"
#include <list>
#include <deque>
#include "Tool.h"
#include "GUI.h"
#include "LuaInterface.h"

enum class PLAYER_GUI_STATE {WORLD, INVENTORY};

class PlayerNotification
{
private:
	ALLEGRO_BITMAP* content;
	int timer;

	PlayerNotification(int t, int w, int h);

public:
	void Draw(int x, int y, int width, int height, int new_timer);
	bool ShouldBeRemoved(int new_timer);
	static PlayerNotification* MakeTextNotification(std::string txt, int w, int h, int t, int fontsize = 30);
};

class PlayerEntity :
    public Entity,
	public GUI,
	private GroundTileMiner
{
private:
	std::string buf;
	mutable std::deque<std::pair<ALLEGRO_COLOR,std::string>> history;
	static ALLEGRO_BITMAP* TEXTURE;
	LuaInterface* luaInterface;
	enum class PLAYER_GUI_STATE guistate;
	int GUItimer;
	char keys_pressed;
	InventoryGUI* inventoryGUI;
	RecipeListGUI* recipeGUI;
	InventoryGUI* hotbarGUI;
	ItemInventory* inventory;
	Tool* pickaxeTool;
	Tool* axeTool;
	Tool* shovelTool;
	Tool* pumpTool;

	std::list<PlayerNotification*> notifications;

	virtual void AddResult(const ItemBundle* b) override;

public:

	void LogToConsole(std::string txt) const;

	void DrawThisGUI() final;
	void Draw() final;

	void KeyDown(ALLEGRO_KEYBOARD_EVENT &event) final;
	void KeyUp(ALLEGRO_KEYBOARD_EVENT &event) final;

	void MouseButtonDown(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonUp(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonMove(ALLEGRO_MOUSE_EVENT &event) final;

	void CharTyped(ALLEGRO_KEYBOARD_EVENT& event) override;

	void PlaceTile(int x, int y);
	void MineTile(int x, int y);

	void GiveConstItem(const Item* item);

	void Tick() final;

	void PushNotification(std::string txt, int fontsize = 30);

	PlayerEntity(World* world, float xpos, float ypos);

	virtual ~PlayerEntity() = default;

	friend WorldChunk;
	friend World;
	friend int main();
};


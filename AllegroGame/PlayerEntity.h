#pragma once
#include "Entity.h"
#include "InventoryGUI.h"
#include "GroundTileMiner.h"
#include "ItemInventory.h"
#include "SimpleInventoryGUI.h"
#include <list>
#include "Tool.h"
#include "GUI.h"

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
	static PlayerNotification* MakeTextNotification(std::string txt, int w, int h, int t);
};

class PlayerEntity :
    public Entity,
	public GUI,
	private GroundTileMiner
{
private:
	enum class PLAYER_GUI_STATE guistate;
	int GUItimer;
	char keys_pressed;
	InventoryGUI* inventoryGUI;
	InventoryGUI* hotbarGUI;
	ItemInventory* inventory;
	Tool* pickaxeTool;
	Tool* axeTool;
	Tool* shovelTool;
	Tool* pumpTool;

	std::list<PlayerNotification*> notifications;

public:

	void DrawThisGUI() final;
	void Draw() final;

	void KeyDown(ALLEGRO_KEYBOARD_EVENT &event) final;
	void KeyUp(ALLEGRO_KEYBOARD_EVENT &event) final;

	void MouseButtonDown(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonUp(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonMove(ALLEGRO_MOUSE_EVENT &event) final;

	void PlaceTile(int x, int y);
	void MineTile(int x, int y);

	void AddItem(Item* item) override;

	void Tick() final;

	PlayerEntity(World* world, float xpos, float ypos);

	virtual ~PlayerEntity() = default;

	friend WorldChunk;
	friend World;
	friend int main();
};


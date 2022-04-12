#pragma once
#include "Entity.h"
#include "InventoryGUI.h"
#include "GroundTileMiner.h"
#include "ItemInventory.h"
#include "SimpleInventoryGUI.h"
#include "RecipeListGUI.h"
#include "DeathGUI.h"
#include <list>
#include <deque>
#include "Consumable.h"
#include "ConsumableItem.h"
#include "ToolItem.h"
#include "ItemBundle.h"
//#include "WeaponItem.h"
class MeleeWeaponItem;
class RangedWeaponItem;
#include "GUI.h"
#include "LuaInterface.h"

enum class PLAYER_GUI_STATE {WORLD, INVENTORY, DEATH, QUEST};

class WaterGroundTile;

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
	public GroundTileMiner
{
public:
	enum PlayerActionMode {
		MELEE = 0x00,
		RANGED = 0x01,
		MINING = 0x02,
		CONFIGURATION = 0x03
	};
private:
	static const float REACHSQ;
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
	DeathGUI* deathgui;
	ToolItem* pickaxeTool;
	ToolItem* axeTool;
	ToolItem* shovelTool;
	ToolItem* pumpTool;
	MeleeWeaponItem* meleeWeapon;
	RangedWeaponItem* rangedWeapon;
	ConsumableItem* consumableItem;

	float hunger;
	const float MAX_HUNGER = 100.f;
	const float HUNGER_LOSS_PER_TICK = .01f;
	const float HEALTH_LOSS_FROM_HUNGER_PER_TICK = .05f;
	float water;
	const float MAX_WATER = 100.f;
	const float WATER_LOSS_PER_TICK = .025f;
	const float HEALTH_LOSS_FROM_WATER_PER_TICK = .05f;


	char mode;

	std::list<PlayerNotification*> notifications;

	virtual void AddResult(const ItemBundle* b) override;

	const static std::string ID;

public:
	static PlayerEntity* current_player;

	virtual bool Mine();

	virtual std::string GetID() const final;

	void LogToConsole(std::string txt) const;

	static bool ConsumeItemCallback(Item* i);

	void DrawThisGUI() final;
	void Draw() final;

	void Consume(Consumable* c);

	void KeyDown(ALLEGRO_KEYBOARD_EVENT &event) final;
	void KeyUp(ALLEGRO_KEYBOARD_EVENT &event) final;

	void MouseButtonDown(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonUp(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonMove(ALLEGRO_MOUSE_EVENT &event) final;

	void CharTyped(ALLEGRO_KEYBOARD_EVENT& event) override;

	void UseTile(int x, int y);
	void MineTile(int x, int y);

	void GiveConstItem(const Item* item);
	void GiveConstItemBundle(const ItemBundle* bundle);

	void Tick() final;

	void ResetAfterDeath();

	void PushNotification(std::string txt, int fontsize = 30);

	PlayerEntity(World* world, float xpos, float ypos);

	virtual ~PlayerEntity() = default;

	friend WorldChunk;
	friend World;
	friend int main();
	friend void deathguicallback();
	friend WaterGroundTile;
};


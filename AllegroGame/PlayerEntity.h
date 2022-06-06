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
#include "QuestGUI.h"
//#include "WeaponItem.h"
class MeleeWeaponItem;
class RangedWeaponItem;
#include "GUI.h"
#include "LuaInterface.h"
#include "AudioMultiTrackCollection.h"

enum class PLAYER_GUI_STATE { WORLD, INVENTORY, DEATH, QUEST };

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
		CONFIGURATION = 0x03,
		BUILDING = 0x04
	};
private:
	std::string buf;
	mutable std::deque<std::pair<ALLEGRO_COLOR,std::string>> history;
	static ALLEGRO_BITMAP* TEXTURE;
	LuaInterface* luaInterface;
	enum class PLAYER_GUI_STATE guistate;
	int historyViewIndex;
	int GUItimer;
	char keys_pressed;
	int selectedHotbarSlot;
	InventoryGUI* inventoryGUI;
	RecipeListGUI* recipeGUI;
	InventoryGUI* hotbarGUI;
	QuestGUI* questGUI;
	ItemInventory* inventory;
	DeathGUI* deathgui;
	ToolItem* pickaxeTool;
	ToolItem* axeTool;
	ToolItem* shovelTool;
	ToolItem* pumpTool;
	MeleeWeaponItem* meleeWeapon;
	RangedWeaponItem* rangedWeapon;

	static std::string NAME;
	static float RANGESQ;
	float hunger;
	static float MAX_HUNGER;
	static float HUNGER_LOSS_PER_TICK;
	static float HEALTH_LOSS_FROM_HUNGER_PER_TICK;
	float water;
	static float MAX_WATER;
	static float WATER_LOSS_PER_TICK;
	static float HEALTH_LOSS_FROM_WATER_PER_TICK;
	static AudioMultiTrackCollection AUDIO_TRACKS;


	char mode;

	std::list<PlayerNotification*> notifications;

	virtual void AddResult(const ItemBundle* b) override;

public:

	void EntityKilledRemote(Entity* e);

	const static std::string ID;

	virtual bool Mine();

	virtual std::string GetID() const final;

	void LogToConsole(std::string txt) const;

	void PreDrawThisGUI() final;
	void PostDrawThisGUI() final;
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

	static void Init(nlohmann::json data);

	void ResetAfterDeath();

	virtual void PlaySound(SoundType t) const final;

	void PushNotification(std::string txt, int fontsize = 30);

	PlayerEntity(World* world, float xpos, float ypos);

	virtual ~PlayerEntity() = default;

	friend WorldChunk;
	friend World;
	friend int main();
	friend WaterGroundTile;
	friend class Consumable;
};


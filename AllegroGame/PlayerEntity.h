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
#include "SimpleToggleTextButtonUIComponent.h"
#include "ToolItem.h"
#include "ItemBundle.h"
#include "QuestGUI.h"
#include "SimpleCraftingGUI.h"
//#include "WeaponItem.h"
class MeleeWeaponItem;
class RangedWeaponItem;
#include "GUI.h"
#include "LuaInterface.h"
#include "PlaceableItem.h"
#include "AudioMultiTrackCollection.h"
#undef PlaySound

enum class PLAYER_GUI_STATE { WORLD, PAUSE, INVENTORY, CRAFTING, DEATH, QUEST, INFO, TILE };

class WaterGroundTile;

class World;
class WorldChunk;

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
	friend class PlayerEntity;
};

class PlayerEntity:
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
	bool godMode = false;
	class PauseMenuGUI :
		public GUI
	{
	public:
		SimpleToggleTextButtonUIComponent* godmode_tb;
		SimpleToggleTextButtonUIComponent* tile_tick_tb;
		SimpleToggleTextButtonUIComponent* entity_tick_tb;
		virtual void PreDrawThisGUI() final;
		PauseMenuGUI(PlayerEntity* p);
	};

	std::string buf;
	char debug = 0;
	bool infoMenu = false;
	bool showHitbox = false;
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
	SimpleCraftingGUI* craftingGUI;
	InventoryGUI* hotbarGUI;
	PauseMenuGUI* pauseGUI;
	QuestGUI* questGUI;
	ItemInventory* inventory;
	DeathGUI* deathgui;
	Item* pickaxeTool;
	Item* axeTool;
	Item* shovelTool;
	Item* pumpTool;
	Item* placeableItem;
	Item* meleeWeapon;
	Item* rangedWeapon;

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

	virtual void LoadAdditionalDataFromFile(std::ifstream& file) override;
	virtual void WriteAdditionalDataToFile(std::ofstream& file) override;

	virtual Entity* Clone(World* world, float x, float y) const override;

	void EntityKilledRemote(Entity* e);

	const static std::string ID;

	virtual bool Mine();

	virtual std::string GetID() const final;

	void LogToConsole(std::string txt) const;

	void PreDrawThisGUI() final;
	void PostDrawThisGUI() final;
	void Draw() final;

	bool KeyDown(ALLEGRO_KEYBOARD_EVENT &event) final;
	bool KeyUp(ALLEGRO_KEYBOARD_EVENT &event) final;

	bool MouseButtonDown(ALLEGRO_MOUSE_EVENT &event) final;
	bool MouseButtonUp(ALLEGRO_MOUSE_EVENT &event) final;
	bool MouseButtonMove(ALLEGRO_MOUSE_EVENT &event) final;

	bool KeyChar(ALLEGRO_KEYBOARD_EVENT& event) override;

	void UseTile(int x, int y);
	void MineTile(int x, int y);

	void GiveConstItem(const Item* item);
	void GiveConstItemBundle(const ItemBundle* bundle);

	void Tick() final;

	static void Init(nlohmann::json data);

	void ResetAfterDeath();

	virtual void PlaySound(SoundType t) const final;

	void PushNotification(std::string txt, int fontsize = 30);
	void DisplayTileGUI(Tile* t, GUI* g);

	InventoryGUI* GetMainInventoryGUI(int offsetx, int offsety);

	PlayerEntity(World* world, float xpos, float ypos);

	virtual ~PlayerEntity() = default;

	friend WorldChunk;
	friend World;
	friend PauseMenuGUI;
	friend int main();
	friend WaterGroundTile;
	friend class Consumable;
};


#pragma once
#include <lua.hpp>
#include <string>
class World;

class LuaInterface
{
private:
	World* world;
	lua_State* state;
public:
	LuaInterface(World* world, bool privileged = false);

	void dostring(std::string str);

	static int lua_GiveItem(lua_State* state);
	static int lua_SetTile(lua_State* state);
	static int lua_SetGroundTile(lua_State* state);
	static int lua_GetTile(lua_State* state);
	static int lua_GetGroundTile(lua_State* state);
	static int lua_Print(lua_State* state);
	static int lua_SetDaytime(lua_State* state);
	static int lua_Teleport(lua_State* state);
	static int lua_SpawnEntity(lua_State* state);
	static int lua_TickTile(lua_State* state);
	static int lua_RandomTickTile(lua_State* state);
};

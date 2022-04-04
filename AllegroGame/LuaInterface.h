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
};
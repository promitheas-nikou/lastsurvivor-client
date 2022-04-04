#include "LuaInterface.h"
#include "World.h"
#include "Item.h"


LuaInterface::LuaInterface(World* world, bool privileged) : world{ world }
{
	state = luaL_newstate();
	luaopen_math(state);
	luaopen_base(state);
	luaopen_string(state);
	luaopen_table(state);
	luaopen_coroutine(state);
	if (privileged)
	{
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_GiveItem, 1);
		lua_setglobal(state, "giveitem");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_SetTile, 1);
		lua_setglobal(state, "settile");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_SetGroundTile, 1);
		lua_setglobal(state, "setgtile");
		luaL_dofile(state, "LuaDefault.lua");
	}

}

void LuaInterface::dostring(std::string str)
{
	luaL_dostring(state, str.c_str());
}

int LuaInterface::lua_GiveItem(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state,lua_upvalueindex(1));
	const_cast<PlayerEntity*>(ptr->world->GetPlayer())->GiveConstItem(MakeItemFromID(lua_tostring(state, 1)));
	return LUA_OK;
}

int LuaInterface::lua_SetTile(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	std::string id = lua_tostring(state, 1);
	int x = lua_tointeger(state, 2);
	int y = lua_tointeger(state, 3);
	delete ptr->world->SetTile(MakeTile(ptr->world, id, x, y), x, y);
	return LUA_OK;
}

int LuaInterface::lua_SetGroundTile(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	std::string id = lua_tostring(state, 1);
	int x = lua_tointeger(state, 2);
	int y = lua_tointeger(state, 3);
	delete ptr->world->SetGroundTile(MakeGroundTile(ptr->world, id, x, y), x, y);
}

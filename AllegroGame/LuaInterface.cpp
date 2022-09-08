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
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_GetTile, 1);
		lua_setglobal(state, "gettile");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_GetGroundTile, 1);
		lua_setglobal(state, "getgtile");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_Print, 1);
		lua_setglobal(state, "consoleprint");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_SetDaytime, 1);
		lua_setglobal(state, "settime");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_Teleport, 1);
		lua_setglobal(state, "teleport");
		lua_pushlightuserdata(state, this);
		lua_pushcclosure(state, &lua_SpawnEntity, 1);
		lua_setglobal(state, "spawn");
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
	Item* i = MakeItemFromID(lua_tostring(state, 1));
	if(i!=nullptr)
	{
		i->SetAmount(lua_tonumber(state,2));
		const_cast<PlayerEntity*>(ptr->world->GetPlayer())->GiveConstItem(i);
	}
	lua_pushboolean(state,i!=nullptr);
	return 1;
}

int LuaInterface::lua_SetTile(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	std::string id = lua_tostring(state, 1);
	int x = lua_tointeger(state, 2);
	int y = lua_tointeger(state, 3);
	Tile* t = MakeTile(ptr->world, id, x, y);
	if(t!=nullptr)
		delete ptr->world->SetTile(t, x, y);
	lua_pushboolean(state,t!=nullptr);
	return 1;
}

int LuaInterface::lua_SetGroundTile(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	std::string id = lua_tostring(state, 1);
	int x = lua_tointeger(state, 2);
	int y = lua_tointeger(state, 3);
	GroundTile* t = MakeGroundTile(ptr->world, id, x, y);
	if(t!=nullptr)
		delete ptr->world->SetGroundTile(t, x, y);
	lua_pushboolean(state,t!=nullptr);
	return 1;
}

int LuaInterface::lua_GetTile(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	lua_pushstring(state,ptr->world->GetTile(lua_tointeger(state,1),lua_tointeger(state,2))->GetID().c_str());
	return 1;
}

int LuaInterface::lua_GetGroundTile(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	lua_pushstring(state,ptr->world->GetGroundTile(lua_tointeger(state,1),lua_tointeger(state,2))->GetID().c_str());
	return 1;
}

int LuaInterface::lua_Print(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	ptr->world->GetPlayer()->LogToConsole(lua_tostring(state, 1));
	return 0;
}

int LuaInterface::lua_SetDaytime(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	ptr->world->gametime = lua_tointeger(state, 1);
	return 0;
}

int LuaInterface::lua_Teleport(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	ptr->world->player->warpAbsolute(lua_tointeger(state, 1), lua_tointeger(state, 2));
	return 0;
}

int LuaInterface::lua_SpawnEntity(lua_State* state)
{
	LuaInterface* ptr = (LuaInterface*)lua_topointer(state, lua_upvalueindex(1));
	ptr->world->AddEntity(MakeEntity(ptr->world, lua_tostring(state, 1), lua_tonumber(state, 2), lua_tonumber(state, 3)));
	return 0;
}

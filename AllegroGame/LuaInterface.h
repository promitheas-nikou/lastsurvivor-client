#pragma once
#include <lua.hpp>

lua_State* CONSOLE_LUA_STATE;

void init_privileged_lua_interface(lua_State* state);

void init_unprivileged_lua_interface(lua_State* state);
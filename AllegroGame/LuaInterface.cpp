#include "LuaInterface.h"

void init_privileged_lua_interface(lua_State* state)
{
	luaopen_math(state);
	luaopen_base(state);
	luaopen_string(state);
	luaopen_table(state);
	luaopen_coroutine(state);
}

void init_unprivileged_lua_interface(lua_State* state)
{
}

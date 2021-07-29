#pragma once
#include "Lua.h"
#include <iostream>
#include <string>
namespace Oak
{
	bool Lua_Check(lua_State* L, int r)
	{
		if (r != LUA_OK)
		{
			const char* error = lua_tostring(L, -1);
			std::cout << error << std::endl;
			return false;
		}
		return true;
	}
	void Lua_Call_Function(lua_State* L, std::string script_name, std::string function_name)
	{
		std::string path = "src/Lua Scripts/" + script_name + ".lua";
		if (Lua_Check(L, luaL_dofile(L, path.c_str())))
		{
			lua_getglobal(L, function_name.c_str());
			if (lua_isfunction(L, -1))
			{
				lua_pcall(L, 0, 0, 0);
			}
		}
	}
	void Lua_Push_Function(lua_State* L, std::string function_name, lua_CFunction function_pointer)
	{
		lua_pushcfunction(L, function_pointer);
		lua_setglobal(L, function_name.c_str());
	}
}
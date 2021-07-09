#pragma once
#include "Lua.h"
#include <vector>
#include <string>
#include <iostream>

namespace Oak
{
	struct LuaScript
	{
		lua_State* L;
		std::string name;
		std::string path;
		std::vector<std::string> functions;
	};

	typedef int (*LuaFunction) (lua_State* L);
	
	class LuaAPI
	{
	public:
		LuaAPI();
		~LuaAPI();

		void AddScriptName(std::string name);
		void PrintScriptName(std::string name);

		void LoadLuaScript(std::string name);

		void ExecuteLuaScript(std::string name);

		void CallLuaFunction(std::string script, std::string function);

		void PushFunctionToLuaScript(std::string script, LuaFunction functionPointer, std::string function);
		void PushFunctionToLuaScript(LuaScript script, LuaFunction functionPointer, std::string function);
	private:
		

		bool CheckLua(lua_State* L, int r)
		{
			if (r != LUA_OK)
			{
				std::string error = lua_tostring(L, -1);
				std::cout << error << std::endl;
				return false;
			}
			return true;
		}
	private:
		std::vector<LuaScript> scripts;
	};

	static LuaAPI gLua;
}
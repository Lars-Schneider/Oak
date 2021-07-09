#include "LuaAPI.h"
#include <iostream>
#include <direct.h>
#include <sstream>
#include <sys/stat.h>

#include<filesystem>
namespace fs = std::filesystem;

namespace Oak
{
	//Lua Functions
	int Print(lua_State* L)
	{
		std::cout << lua_tostring(L, -1);
		return 1;
	}

	LuaAPI::LuaAPI()
	{
		scripts = std::vector<LuaScript>();
	}

	LuaAPI::~LuaAPI()
	{

	}

	void LuaAPI::AddScriptName(std::string name)
	{
		LuaScript script;
		script.name = name;
		scripts.emplace_back(script);
	}

	void LuaAPI::PrintScriptName(std::string name)
	{
		std::vector<LuaScript>::iterator it;
		for (it = scripts.begin(); it < scripts.end(); it++)
		{
			if(it->name == name)
			std::cout << it->path << std::endl;
		}
	}

	void LuaAPI::LoadLuaScript(std::string name)
	{
		/*
		std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
		std::cout << parentDir;

		if (_mkdir(parentDir.append("bin/Oak/x64/Debug/src/Lua Scripts").c_str()) != 0)
		{

		}
		*/

		LuaScript script;
		script.L = luaL_newstate();
		script.name = name;
		std::string path = "src/Lua Scripts/" + name + ".lua";
		script.path = path;
		script.functions = std::vector<std::string>();
		PushFunctionToLuaScript(script, (LuaFunction) Print, "Print");
		scripts.emplace_back(script);
	}

	void LuaAPI::PushFunctionToLuaScript(std::string script, LuaFunction functionPointer, std::string function)
	{
		std::vector<LuaScript>::iterator it;
		for (it = scripts.begin(); it < scripts.end(); it++)
		{
			if (it->name == script)
			{
				lua_pushcfunction(it->L, functionPointer);
				lua_setglobal(it->L, function.c_str());
				it->functions.emplace_back(function);
				return;
			}
		}
	}

	void Oak::LuaAPI::PushFunctionToLuaScript(LuaScript script, LuaFunction functionPointer, std::string function)
	{
		lua_pushcfunction(script.L, functionPointer);
		lua_setglobal(script.L, function.c_str());
		script.functions.emplace_back(function);
	}

	void LuaAPI::ExecuteLuaScript(std::string name)
	{
		std::vector<LuaScript>::iterator it;
		for (it = scripts.begin(); it < scripts.end(); it++)
		{
			if (it->name == name)
				if (luaL_dofile(it->L, it->path.c_str()))
				{
					std::cout << "ERROR";
				}
		}
	}

	void LuaAPI::CallLuaFunction(std::string script, std::string function)
	{
		std::vector<LuaScript>::iterator it;
		for (it = scripts.begin(); it < scripts.end(); it++)
		{
			if (it->name == script)
			{
				if (CheckLua(it->L, luaL_dofile(it->L, it->path.c_str())))
				{
					lua_getglobal(it->L, function.c_str());
					if (lua_isfunction(it->L, -1))
					{
						lua_pcall(it->L, 0, 0, 0);
					}
				}
				return;
			}
		}
	}
}
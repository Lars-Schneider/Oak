#pragma once
#include <src/ECS/ECS.h>
#include "Lua.h"
#include <string>
#include <iostream>
namespace Oak
{
	class ECS_Instace
	{
	public:
		ECS_Manager* manager;
	};

	ECS_Instace* Lua_ECS_instance;

	int ECS_Lua_Get_X(lua_State* L)
	{
		Entity e = Lua_ECS_instance->manager->Get_Entity(lua_tostring(L, -1));
		lua_pushinteger(L, Lua_ECS_instance->manager->Get_Position(e).x);
		return 1;
	}

	int ECS_Lua_Set_X(lua_State* L)
	{
		Entity e = Lua_ECS_instance->manager->Get_Entity(lua_tostring(L, -2));
		Lua_ECS_instance->manager->Get_Position(e).x = std::stoi(lua_tostring(L, -1));
		return 1;
	}

	int Print(lua_State* L)
	{
		std::cout << lua_tostring(L, -1) << "\n";
		return 1;
	}

	void ECS_Lua_Push_Functions(lua_State* L)
	{
		Lua_Push_Function(L, "Get_X", ECS_Lua_Get_X);
		Lua_Push_Function(L, "Set_X", ECS_Lua_Set_X);
		Lua_Push_Function(L, "Print", Print);
	}

	void ECS_Lua_Add_Script(Entity entity)
	{
		ECS_Script_c script;
		script.L = luaL_newstate();
		ECS_Lua_Push_Functions(script.L);
		Lua_ECS_instance->manager->component_array_manager.Add_Script(entity, script);
	}

	
}
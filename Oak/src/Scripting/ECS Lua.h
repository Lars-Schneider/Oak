#pragma once
#include <src/ECS/ECS.h>
#include "Lua.h"
#include <string>
#include <iostream>

namespace Oak
{
	ECS_Manager* manager;

	int width;
	int height;

	namespace Lua
	{
		int ECS_Lua_Get_X(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -1));
			lua_pushnumber(L, manager->Get_Transform(e).x);
			return 1;
		}

		int ECS_Lua_Set_X(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -2));
			manager->Get_Transform(e).x = std::stod(lua_tostring(L, -1));
			return 1;
		}

		int ECS_Lua_Get_Y(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -1));
			lua_pushnumber(L, manager->Get_Transform(e).y);
			return 1;
		}

		int ECS_Lua_Set_Y(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -2));
			manager->Get_Transform(e).y = std::stod(lua_tostring(L, -1));
			return 1;
		}

		int ECS_Lua_Get_W(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -1));
			lua_pushnumber(L, manager->Get_Transform(e).w);
			return 1;
		}

		int ECS_Lua_Set_W(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -2));
			manager->Get_Transform(e).w = std::stod(lua_tostring(L, -1));
			return 1;
		}

		int ECS_Lua_Get_H(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -1));
			lua_pushnumber(L, manager->Get_Transform(e).h);
			return 1;
		}

		int ECS_Lua_Set_H(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -2));
			manager->Get_Transform(e).h = std::stod(lua_tostring(L, -1));
			return 1;
		}

		int ECS_Lua_Get_VX(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -1));
			lua_pushnumber(L, manager->Get_Velocity(e).vx);
			return 1;
		}
		int ECS_Lua_Set_VX(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -2));
			manager->Get_Velocity(e).vx = std::stod(lua_tostring(L, -1));
			return 1;
		}
		int ECS_Lua_Get_VY(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -1));
			lua_pushnumber(L, manager->Get_Velocity(e).vy);
			return 1;
		}
		int ECS_Lua_Set_VY(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -2));
			manager->Get_Velocity(e).vy = std::stod(lua_tostring(L, -1));
			return 1;
		}

		int ECS_Lua_Move(lua_State* L)
		{
			Entity e = manager->Get_Entity(lua_tostring(L, -3));
			manager->Get_Transform(e).x += std::stod(lua_tostring(L, -2));
			manager->Get_Transform(e).y += std::stod(lua_tostring(L, -1));
			return 1;
		}

		int Print(lua_State* L)
		{
			std::cout << lua_tostring(L, -1) << "\n";
			return 1;
		}

		int Screen_Width(lua_State* L)
		{
			lua_pushnumber(L, width);
			return 1;
		}

		int Screen_Height(lua_State* L)
		{
			lua_pushnumber(L, height);
			return 1;
		}
	}


	void ECS_Lua_Push_Functions(lua_State* L)
	{
		Lua_Push_Function(L, "Get_X", Lua::ECS_Lua_Get_X);
		Lua_Push_Function(L, "Set_X", Lua::ECS_Lua_Set_X);
		Lua_Push_Function(L, "Get_Y", Lua::ECS_Lua_Get_Y);
		Lua_Push_Function(L, "Set_Y", Lua::ECS_Lua_Set_Y);

		Lua_Push_Function(L, "Get_W", Lua::ECS_Lua_Get_W);
		Lua_Push_Function(L, "Set_W", Lua::ECS_Lua_Set_W);
		Lua_Push_Function(L, "Get_H", Lua::ECS_Lua_Get_H);
		Lua_Push_Function(L, "Set_H", Lua::ECS_Lua_Set_H);

		Lua_Push_Function(L, "Get_VX", Lua::ECS_Lua_Get_VX);
		Lua_Push_Function(L, "Set_VX", Lua::ECS_Lua_Set_VX);
		Lua_Push_Function(L, "Get_VY", Lua::ECS_Lua_Get_VY);
		Lua_Push_Function(L, "Set_VY", Lua::ECS_Lua_Set_VY);

		Lua_Push_Function(L, "Move", Lua::ECS_Lua_Move);

		Lua_Push_Function(L, "Print", Lua::Print);

		Lua_Push_Function(L, "Screen_Width", Lua::Screen_Width);
		Lua_Push_Function(L, "Screen_Height", Lua::Screen_Height);
	}

	void ECS_Lua_Add_Script(Entity entity)
	{
		ECS_Script_c script;
		script.L = luaL_newstate();
		script.path = manager->Get_Tag(entity).tag.c_str();
		ECS_Lua_Push_Functions(script.L);
		manager->component_array_manager.Add_Script(entity, script);
	}
}
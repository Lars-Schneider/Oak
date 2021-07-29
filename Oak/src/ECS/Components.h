#pragma once
#include "src/Types.h"
#include "src/Scripting/Lua.h"
namespace Oak
{
	struct ECS_Tag_c
	{
		const char* tag;
	};
	struct ECS_Position_c
	{
		f32 x;
		f32 y;
	};
	struct ECS_Script_c
	{
		lua_State* L;
	};
}
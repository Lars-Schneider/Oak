#pragma once
#include "src/Types.h"
#include "src/Scripting/Lua.h"
namespace Oak
{
	struct ECS_Tag_c
	{
		const char* tag;
	};

	struct ECS_Transform_c
	{
		f32 x;
		f32 y;
		f32 w;
		f32 h;
	};

	struct ECS_Velocity_c
	{
		f32 vx;
		f32 vy;
	};

	struct ECS_Script_c
	{
		lua_State* L;
		const char* path;
	};
	struct ECS_SDL_Rect_c
	{
		i32 r;
		i32 g;
		i32 b;
		i32 a;
	};
}
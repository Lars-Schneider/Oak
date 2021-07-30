#pragma once
#include "Components.h"
#include "Component Array/ECS_Component_Array.h"
#include <iostream>
namespace Oak
{
	class ECS_Component_Array_Manager
	{
	public:
		inline ECS_Component_Array<ECS_Tag_c>& Tag_Array() { return tag_array; }
		inline ECS_Component_Array<ECS_Position_c>& Position_Array() { return position_array; }
		inline ECS_Component_Array<ECS_Script_c>& Script_Array() { return script_array; }
		inline ECS_Component_Array<ECS_SDL_Rect_c>& Rect_Array() { return rect_array; }

		void Add_Tag(Entity entity, ECS_Tag_c tag)
		{
			tag_array[entity] = tag;
			tag_array.Bool_Array()[entity] = true;
		}

		void Add_Position(Entity entity, ECS_Position_c position)
		{
			position_array[entity] = position;
			position_array.Bool_Array()[entity] = true;
		}

		void Add_Script(Entity entity, ECS_Script_c script)
		{
			script_array[entity] = script;
			script_array.Bool_Array()[entity] = true;
		}

		void Add_Rect(Entity entity, ECS_SDL_Rect_c rect)
		{
			rect_array[entity] = rect;
			rect_array.Bool_Array()[entity] = true;
		}
	private:
		ECS_Component_Array<ECS_Tag_c> tag_array{};
		ECS_Component_Array<ECS_Position_c> position_array{};
		ECS_Component_Array<ECS_Script_c> script_array{};
		ECS_Component_Array<ECS_SDL_Rect_c> rect_array{};
	};
}
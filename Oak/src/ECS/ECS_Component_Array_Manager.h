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
		inline ECS_Component_Array<ECS_Transform_c>& Transform_Array() { return transform_array; }
		inline ECS_Component_Array<ECS_Script_c>& Script_Array() { return script_array; }
		inline ECS_Component_Array<ECS_SDL_Rect_c>& Rect_Array() { return rect_array; }
		inline ECS_Component_Array<ECS_Velocity_c>& Velocity_Array() { return velocity_array; }

		void Add_Tag(Entity entity, ECS_Tag_c tag)
		{
			tag_array[entity] = tag;
			tag_array.Bool_Array()[entity] = true;
		}

		void Add_Position(Entity entity, ECS_Transform_c position)
		{
			transform_array[entity] = position;
			transform_array.Bool_Array()[entity] = true;
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

		void Add_Velocity(Entity entity, ECS_Velocity_c velocity)
		{
			velocity_array[entity] = velocity;
			velocity_array.Bool_Array()[entity] = true;
		}
	private:
		ECS_Component_Array<ECS_Tag_c> tag_array{};
		ECS_Component_Array<ECS_Transform_c> transform_array{};
		ECS_Component_Array<ECS_Script_c> script_array{};
		ECS_Component_Array<ECS_SDL_Rect_c> rect_array{};
		ECS_Component_Array<ECS_Velocity_c> velocity_array{};
	};
}
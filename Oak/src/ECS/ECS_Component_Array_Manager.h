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

		void Add_Tag(Entity entity, ECS_Tag_c tag)
		{
			tag_array[entity] = tag;
		}

		void Add_Position(Entity entity, ECS_Position_c position)
		{
			position_array[entity] = position;
		}

		void Add_Script(Entity entity, ECS_Script_c script)
		{
			script_array[entity] = script;
		}
	private:
		ECS_Component_Array<ECS_Tag_c> tag_array{};
		ECS_Component_Array<ECS_Position_c> position_array{};
		ECS_Component_Array<ECS_Script_c> script_array{};
	};
}
#pragma once
#include "Components.h"
#include "Component Array/ECS_Component_Array.h"
namespace Oak
{
	class ECS_Component_Array_Manager
	{
	public:
		inline ECS_Component_Array<ECS_Tag_c> Tag_Array() { return tag_array; }
		inline ECS_Component_Array<ECS_Position_c> Position_Array() { return position_array; }

		void Add_Tag(Entity entity, ECS_Tag_c tag)
		{
			tag_array[entity] = tag;
		}

		void Add_Position(Entity entity, ECS_Position_c position)
		{
			position_array[entity] = position;
		}
	private:
		ECS_Component_Array<ECS_Tag_c> tag_array{};
		ECS_Component_Array<ECS_Position_c> position_array{};
	};
}
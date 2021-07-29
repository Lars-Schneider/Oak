#pragma once
#include <src/ECS/ECS_Component_Array_Manager.h>
namespace Oak
{
	class ECS_Manager
	{
	public:
		Entity Create_Entity()
		{
			if (latest_entity < OAK_ECS_MAX_ENTITES)
				return latest_entity++;
		}
		void Add_Tag(Entity entity, ECS_Tag_c tag)
		{
			component_array_manager.Add_Tag(entity, tag);
		}
		ECS_Tag_c Get_Tag(Entity entity)
		{
			return component_array_manager.Tag_Array()[entity];
		}
		void Add_Position(Entity entity, ECS_Position_c position)
		{
			component_array_manager.Add_Position(entity, position);
		}
		ECS_Position_c Get_Position(Entity entity)
		{
			return component_array_manager.Position_Array()[entity];
		}
	private:
		ECS_Component_Array_Manager component_array_manager{};
		Entity latest_entity;
	};
}
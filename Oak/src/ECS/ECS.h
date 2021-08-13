#pragma once
#include <src/ECS/ECS_Component_Array_Manager.h>
#include <string>
#include <iostream>
namespace Oak
{
	class ECS_Manager
	{
	public:
		ECS_Manager()
		{
			latest_entity = 0;
		}
		Entity Create_Entity()
		{
			if (latest_entity < OAK_ECS_MAX_ENTITES)
				return latest_entity++;
		}
		Entity Get_Entity(std::string entity_tag)
		{
			for (Entity e = 0; e < OAK_ECS_MAX_ENTITES; e++)
			{
				if (component_array_manager.Tag_Array()[e].tag == entity_tag)
				{
					return e;
				}
			}
			//std::cout << "\n\n\n" << entity_tag<< "\n";
		}
		
		inline ECS_Component_Array<ECS_Tag_c>& Tag_Array() { return component_array_manager.Tag_Array(); }
		inline ECS_Component_Array<ECS_Transform_c>& Transform_Array() { return component_array_manager.Transform_Array(); }
		inline ECS_Component_Array<ECS_Script_c>& Script_Array() { return component_array_manager.Script_Array(); }
		inline ECS_Component_Array<ECS_SDL_Rect_c>& Rect_Array() { return component_array_manager.Rect_Array(); }
		inline ECS_Component_Array<ECS_Velocity_c>& Velocity_Array() { return component_array_manager.Velocity_Array(); }

		void Add_Tag(Entity entity, ECS_Tag_c tag)
		{
			component_array_manager.Add_Tag(entity, tag);
		}
		ECS_Tag_c& Get_Tag(Entity entity)
		{
			return component_array_manager.Tag_Array()[entity];
		}
		bool Has_Tag(Entity entity)
		{
			return component_array_manager.Tag_Array().Bool_Array()[entity];
		}


		void Add_Transform(Entity entity, ECS_Transform_c position)
		{
			component_array_manager.Add_Position(entity, position);
		}
		ECS_Transform_c& Get_Transform(Entity entity)
		{
			return component_array_manager.Transform_Array()[entity];
		}
		bool Has_Transform(Entity entity)
		{
			return component_array_manager.Transform_Array().Bool_Array()[entity];
		}

		void Add_Rect(Entity entity, ECS_SDL_Rect_c rect)
		{
			component_array_manager.Add_Rect(entity, rect);
		}
		ECS_SDL_Rect_c& Get_Rect(Entity entity)
		{
			return component_array_manager.Rect_Array()[entity];
		}
		bool Has_Rect(Entity entity)
		{
			return component_array_manager.Rect_Array().Bool_Array()[entity];
		}

		ECS_Script_c& Get_Script(Entity entity)
		{
			return component_array_manager.Script_Array()[entity];
		}
		bool Has_Script(Entity entity)
		{
			return component_array_manager.Script_Array().Bool_Array()[entity];
		}
	
		void Add_Velocity(Entity entity, ECS_Velocity_c velocity)
		{
			component_array_manager.Add_Velocity(entity, velocity);
		}
		ECS_Velocity_c& Get_Velocity(Entity entity)
		{
			return component_array_manager.Velocity_Array()[entity];
		}
		bool Has_Velocity(Entity entity)
		{
			return component_array_manager.Velocity_Array().Bool_Array()[entity];
		}
	
	public:
		ECS_Component_Array_Manager component_array_manager{};
		Entity latest_entity;
	};
}
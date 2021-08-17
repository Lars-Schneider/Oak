#pragma once
#include "src/ECS/ECS_Types.h"
#include <vector>
namespace Oak
{
	template<typename T>
	class ECS_Component_Array
	{
	public:
		T* ComponentArray()
		{
			return component_array;
		}
		bool* BoolArray()
		{
			return with_component;
		}
		std::vector<T>& ComponentVector()
		{
			return component_vector;
		}
		std::vector<Entity>& EntityVector()
		{
			return entity_vector;
		}

		void Add(Entity entity, T component)
		{
			component_array[entity] = component;
			with_component[entity] = true;
			component_vector.push_back(component);
			entity_vector.push_back(entity);
		}

		T& Get(Entity entity)
		{
			return component_array[entity];
		}

		bool Has(Entity entity)
		{
			return with_component[entity];
		}
	private:
		T component_array[OAK_ECS_MAX_ENTITES]{};
		bool with_component[OAK_ECS_MAX_ENTITES]{false};
		std::vector<T> component_vector;
		std::vector<Entity> entity_vector;
	};
}
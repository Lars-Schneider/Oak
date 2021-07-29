#pragma once
#include "src/ECS/ECS_Types.h"
namespace Oak
{
	template<typename T>
	class ECS_Component_Array
	{
	public:
		inline T* Component_Array()
		{
			return component_array;
		}
		T& operator [] (Entity index)
		{
			if(index < OAK_ECS_MAX_ENTITES)
			return component_array[index];
		}
	private:
		T component_array[OAK_ECS_MAX_ENTITES];
	};
}
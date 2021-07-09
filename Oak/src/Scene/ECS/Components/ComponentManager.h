#pragma once
#include <iostream>
#include "ComponentArray.h"
/*Component Manager*/
class ECSComponentManager
{
public:
	ECSComponentManager()
	{

	}
	~ECSComponentManager()
	{

	}

	template<typename T>
	void RegisterComponent()
	{
		component_type_id[current_component_id] = typeid(T).name();

		component_arrays[current_component_id] = ECSComponentArray<T>();
		current_component_id++;
	}

	template<typename T>
	void AddComponent(Entity e, T c)
	{
		GetComponentArray<T>()->AddComponent(e, c);
		component_type_id[current_component_id] = typeid(T).name();
		current_component_id++;
	}

	template<typename T>
	T& GetComponent(Entity e)
	{
		return GetComponentArray<T>()->GetComponent(e);
	}

	template<typename T>
	ECSComponentArray<T>* GetComponentArray()
	{
		return (ECSComponentArray<T>*)(&component_arrays[GetComponentTypeID<T>()]);
	}

private:
	IComponentArray component_arrays[MAX_COMPONENTS]{};
	const char* component_type_id[MAX_COMPONENTS]{};
	int current_component_id{ 0 };

private:
	template<typename T>
	int GetComponentTypeID()
	{
		const char* type_name = typeid(T).name();
		int index = 0;
		for (auto& name : component_type_id)
		{
			if (name == type_name)
			{
				return index;
			}
			index++;
		}
	}
};
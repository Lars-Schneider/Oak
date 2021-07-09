#pragma once
#include "../ECSTypes.h"
class IComponentArray
{
public:

	virtual ~IComponentArray() = default;
};


template<typename T>
class ECSComponentArray : public IComponentArray
{
public:
	void AddComponent(Entity e, T c)
	{
		component_array[e] = c;
	}
	T& GetComponent(Entity e)
	{
		return component_array[e];
	}
private:
	T component_array[MAX_ENTITIES]{};
};
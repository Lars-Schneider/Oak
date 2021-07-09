#pragma once
#include "../Scene/ECS/ECSTypes.h"
#include <iostream>
#include "../Scene/ECS/Components/Components.h"
#include "../Scene/ECS/Components/ComponentManager.h"

class TagSystem
{
public:
	TagSystem()
	{

	}
	void Update(ECSComponentManager& cm, Entity max_entity)
	{
		for (Entity entity = 0; entity < max_entity; entity++)
		{
			std::cout << "\n" << cm.GetComponent<TagComponent>(entity).tag << "\n";
		}
	}
};
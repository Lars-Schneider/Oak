#pragma once
#include "../Scene/ECS/ECSTypes.h"
class ECSEntityManager
{
public:
	Entity CreateEntity()
	{
		return current_entity_id++;
	}

	Entity CurrentEntity()
	{
		return current_entity_id;
	}
private:
	Entity current_entity_id{ 0 };
};
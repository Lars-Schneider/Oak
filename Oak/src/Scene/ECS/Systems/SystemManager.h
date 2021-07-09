#pragma once
#include "Systems.h"

class ECSSystemManager
{
public:
	ECSSystemManager()
	{
		tag_system = TagSystem();
	}
	void UpdateSystems(ECSComponentManager& cm, Entity max_entity)
	{
		tag_system.Update(cm, max_entity);
	}
private:
	TagSystem tag_system;
};
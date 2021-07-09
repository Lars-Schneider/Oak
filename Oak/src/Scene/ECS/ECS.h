#pragma once
#include "Components/ComponentManager.h"
#include "Systems/SystemManager.h"
#include "Entities/EntityManager.h"
//ECS
class ECS
{
public:
	ECS()
	{
		entity_manager = ECSEntityManager();
		component_manager = ECSComponentManager();
		system_manager = ECSSystemManager();
		RegisterComponent<TagComponent>();
	}
	Entity CreateEntity()
	{
		return entity_manager.CreateEntity();
	}


	template<typename T>
	void AddComponent(Entity e, T c)
	{
		component_manager.AddComponent<T>(e, c);
	}

	template<typename T>
	T& GetComponent(Entity e)
	{
		return component_manager.GetComponent<T>(e);
	}

	void Update()
	{
		system_manager.UpdateSystems(component_manager, entity_manager.CurrentEntity());
	}
private:
	ECSEntityManager entity_manager;
	ECSComponentManager component_manager;
	ECSSystemManager system_manager;

private:

	template<typename T>
	void RegisterComponent()
	{
		component_manager.RegisterComponent<T>();
	}
};
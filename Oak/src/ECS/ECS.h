#pragma once
#include "Components.h"
#include "Component Array/ECS_Component_Array.h"
#include <iostream>
#include <unordered_map>
namespace Oak
{
	class ECS
	{
	public:
		Entity CreateEntity()
		{
			return latest_entity++;
		}

		Entity GetEntity(std::string tag)
		{
			return tag_map[tag];
		}

		//Tag accessors
		void AddTag(Entity entity, ECS_Tag_c tag)
		{
			tag_array.Add(entity, tag);
			std::pair<std::string, Entity> pair(tag.tag, entity);
			tag_map.insert(pair);
		}
		ECS_Tag_c& GetTag(Entity entity)
		{
			return tag_array.Get(entity);
		}
		bool HasTag(Entity entity)
		{
			return tag_array.Has(entity);
		}
		std::vector<ECS_Tag_c>& Tags()
		{
			return tag_array.ComponentVector();
		}
		std::vector<Entity>& WithTags()
		{
			return tag_array.EntityVector();
		}

		//Transform accessors 
		void AddTransform(Entity entity, ECS_Transform_c transform)
		{
			transform_array.Add(entity, transform);
		}
		ECS_Transform_c& GetTransform(Entity entity)
		{
			return transform_array.Get(entity);
		}
		bool HasTransform(Entity entity)
		{
			return transform_array.Has(entity);
		}
		std::vector<ECS_Transform_c> Transforms()
		{
			return transform_array.ComponentVector();
		}
		std::vector<Entity>& WithTransforms()
		{
			return transform_array.EntityVector();
		}


		//Script accessors
		void AddScript(Entity entity, ECS_Script_c script)
		{
			script_array.Add(entity, script);
		}
		ECS_Script_c& GetScript(Entity entity)
		{
			return script_array.Get(entity);
		}
		bool HasScript(Entity entity)
		{
			return script_array.Has(entity);
		}
		std::vector<ECS_Script_c> Scripts()
		{
			return script_array.ComponentVector();
		}
		std::vector<Entity>& WithScripts()
		{
			return script_array.EntityVector();
		}


		//Quad accessors
		void AddQuad(Entity entity, ECS_Quad_c quad)
		{
			quad_array.Add(entity, quad);
		}
		ECS_Quad_c& GetQuad(Entity entity)
		{
			return quad_array.Get(entity);
		}
		bool HasQuad(Entity entity)
		{
			return quad_array.Has(entity);
		}
		std::vector<ECS_Quad_c> Quads()
		{
			return quad_array.ComponentVector();
		}
		std::vector<Entity>& WithQuads()
		{
			return quad_array.EntityVector();
		}

		Entity latest_entity = 0;
	private:
		

		std::unordered_map<std::string, Entity> tag_map;

		ECS_Component_Array<ECS_Tag_c> tag_array{};
		ECS_Component_Array<ECS_Transform_c> transform_array{};
		ECS_Component_Array<ECS_Script_c> script_array{};
		ECS_Component_Array<ECS_Quad_c> quad_array{};
		ECS_Component_Array<ECS_Velocity_c> velocity_array{};
	};
}
#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"
#include<vector>

// Forward decleration
namespace sudo { namespace ecs {
		class Entity;
} }

namespace sudo { namespace sudo_system {

	class WorldSystem : public SudoSystem, public SudoBehaviour {
	private:
		std::vector<ecs::Entity*> m_entityList; // vector list of all the entities
		unsigned char m_isActive;

	private:
		/* Private constructor, singleton class */
		WorldSystem() { }
		static WorldSystem *_instance;

	public:
		/* Method to get pointer to system */
		static WorldSystem *Instance();

		/* Base class methods */
		void Enable() override;
		void Disable() override;
		void CleanUp() override;

		/* Entity list return */
		const std::vector<ecs::Entity*> GetEntityList();

		/* Calls start on entity */
		void Start() override;

		/* Updates all entities */
		void Update(float deltaTime) override;

		/* Calls LateUpdate on all entities */
		void LateUpdate(float deltaTime) override;

		/* Calls Render on every entitiy */
		void Render() override;

		/* Adds a entity to entity list */
		void AddEntity(ecs::Entity *a_entityToAdd);

		/* Deletes entity */
		/* This will get called by Update after it is done updating all the entities, this to avoid any nullptr errors*/
		void RemoveEntity(ecs::Entity *a_entityToRemove);
	};

} } 
#pragma once

#include"sudo_system.h"
#include<vector>

// Forward decleration
namespace sudo { namespace ecs {

		class Entity;

} }

namespace sudo { namespace sudo_system {

	class WorldSystem : public SudoSystem {
	private:
		std::vector<ecs::Entity*> m_entityList; // standarized list of all the entities
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

		/* Updates all entities */
		void Update() override;

		/* Calls start on entity */
		void Start() override;

		/* Adds a entity to entity list */
		void AddEntity(ecs::Entity *a_entityToAdd);

		/* Removes entity with a_name */
		/* Deletes all entites with a_name if a_deleteAll equels true */
		//void RemoveEntity(const char* a_name, unsigned char a_deleteAll);
	};

} } 
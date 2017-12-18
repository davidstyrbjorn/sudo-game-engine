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


		// Behaviour methods
		void Start() override;
		void Update(float deltaTime) override;
		void LateUpdate(float deltaTime) override;
		void Render() override;

		// Entity handling
		const std::vector<ecs::Entity*> GetEntityList();
		void AddEntity(ecs::Entity *a_entityToAdd);
		void RemoveEntity(ecs::Entity *a_entityToRemove);
		void RemoveAllEntitiesWithID(const unsigned char a_id);
			
		std::vector<ecs::Entity*> GetEntitiesWithID(const unsigned char a_id);
	};

} } 
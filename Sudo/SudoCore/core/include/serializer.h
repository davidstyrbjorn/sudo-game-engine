#pragma once

namespace sudo {

	// Forward decleartions
	namespace ecs {
		class Entity;
	}
	namespace sudo_system {
		class WorldSystem;
	}

	class Serializer {
	public:
		Serializer() { }

		//////////////
		// Called outside of class
		// Serializes every entity inside a_world
		void SerializeWorld(const sudo_system::WorldSystem& a_world);
		
	private:
		/////////////
		// Called by the serializing process
		// Returns the data to serialize for given entity
		char* GetSeralizedata(const ecs::Entity& a_entity);
	};
}
#pragma once

#include<vector>
#include"component.h"

namespace sudo { namespace ecs {

	class Entity {
	private:
		std::vector<Component*> m_components;  
		char* m_name;

	public:
		/* Entity Constructor */
		Entity(char* a_name);

		/* Entity Destructor */
		~Entity();

		/* Updates all components inside m_components list */
		void Update();

		/* Calls start on all components inside m_components list */
		void Start();

		/* Adds a_component to the components list */
		void AddComponent(Component *a_component);

		/* Removes component with a_name from the components list */
		void RemoveComponent(const char* a_name);

		/* Returns the component inside the components list with a_name */
		Component* GetComponent(char* a_name);

		/* Sets m_name */
		void SetName(char* a_name);

		/* Returns m_name */
		char* GetName();
	};
	
} }
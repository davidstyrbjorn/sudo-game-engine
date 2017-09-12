#pragma once

#include<vector>
#include"component.h"

#include<type_traits>

#include"transform_component.h"

namespace sudo { namespace ecs {

	class Entity {
	private:
		std::vector<Component*> m_components;  
		char* m_name;

	public:
		Transform *transform;

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
		template<typename TemplateClass>
		TemplateClass* GetComponent(const char* a_name)
		{
			// Look for component
			for (unsigned int i = 0; i < m_components.size(); ++i) {
				if (m_components[i]->GetName() == a_name) {
					// We found the component at index i inside the list
					// Assert here to check if ComponentType is derived from Component base class
					static_assert(std::is_base_of<Component, TemplateClass>::value, "Get Component in-argument ERROR!");
					return static_cast<TemplateClass*>(m_components[i]);
				}
			}

			return nullptr;
		}

		/* Getter for this->components */
		const std::vector<Component*> GetComponentList() { return m_components; }

		/* Sets m_name */
		void SetName(char* a_name);

		/* Returns m_name */
		char* GetName();
	};
	
} }
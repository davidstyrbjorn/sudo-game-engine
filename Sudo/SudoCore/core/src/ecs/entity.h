#pragma once

#include<vector>
#include"component.h"

#include<type_traits>

#include<string>

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

		// class sudo::ecs::class_name
		/* Returns the component inside the components list with a_name */
		template<typename TemplateClass>
		TemplateClass* GetComponent()
		{
			// Getting component name from TemplateClass
			std::string _componentName = "";
			for (int i = 0; i < strlen(typeid(TemplateClass).name()); i++) {
				// After 17 characters the namespace stuff is gone
				if (i >= 17) {
					_componentName += typeid(TemplateClass).name()[i];
				}
			}

			// Look for component
			for (unsigned int i = 0; i < m_components.size(); ++i) {
				//std::cout << _componentName << " " << m_components[i]->GetName() << std::endl;
				if (m_components[i]->GetName() == _componentName) {
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
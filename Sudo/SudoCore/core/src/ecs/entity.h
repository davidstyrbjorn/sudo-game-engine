#pragma once

#include<vector>
#include<type_traits>
#include<string>

namespace sudo { namespace ecs {

	class Component;
	class Transform;

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
		void Update(float deltaTime);

		/* Calls start on all components inside m_components list */
		void Start();

		/* Adds a_component to the components list */
		Component* AddComponent(Component *a_component);

		// class sudo::ecs::class_name
		/* Returns the component inside the components list with a_name */
		template<typename TemplateClass>
		TemplateClass* GetComponent()
		{			
			// Look for component
			for (unsigned int i = 0; i < m_components.size(); ++i) 
			{
				if (typeid(*m_components[i]).name() == typeid(TemplateClass).name())
				{
					// We found the component at index i inside the list
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
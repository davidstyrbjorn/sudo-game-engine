#include"entity.h"

namespace sudo { namespace ecs {

	void Entity::Update() 
	{
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->IsActive()) { // Check if the component is active
				m_components[i]->Update();
			}
		}
	}

	void Entity::Start() 
	{
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->IsActive()) {
				m_components[i]->Start();
			}
		}
	}

	void Entity::AddComponent(Component *a_component) 
	{
		/* Check if the component already exists */
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->GetName() == a_component->GetName()) {
				// Message that the component exists already
				return;
			}
		}

		/* Push back the component into the list */
		m_components.push_back(a_component);
	}

	Component* Entity::GetComponent(char* a_name) 
	{
		/* Loop through and return component with a_name */
		for (int i = 0; i < m_components.size(); i++) { // Loop through each component 
			if (m_components[i]->GetName() == a_name) { // Compare name
				return m_components[i]; // Update the component 
			}
		}

		return nullptr;
	}

	void Entity::SetName(char* a_name)
	{
		m_name = a_name;
	}

	char* Entity::GetName() 
	{
		return m_name;
	}
	
} }
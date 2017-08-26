#include"entity.h"
#include"../systems/world_system.h"
#include"../debug.h"

namespace sudo { namespace ecs {

	Entity::~Entity()
	{

	}

	Entity::Entity(char* a_name) : m_name(a_name) 
	{
		system::WorldSystem *world = system::WorldSystem::Instance();
		world->AddEntity(this);
	}

	void Entity::Update()
	{
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->IsActive() && !m_components[i]->GetDestroyTrigger()) { // Check if the component is active
				m_components[i]->Update();
			}
			else if (m_components[i]->GetDestroyTrigger()) {
				std::vector<Component*>::iterator it;
				for (it = m_components.begin(); it != m_components.end(); ) {
					if ((*it)->GetDestroyTrigger()) {
						delete * it;
						it = m_components.erase(it);
					}
					else {
						++it;
					}
				}
			}
		}
	}

	void Entity::Start() 
	{
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->IsActive()) { // Check if the component is active
				m_components[i]->Start();
			}
		}
	}

	void Entity::AddComponent(Component *a_component) 
	{
		/* Check if the component already exists */
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->GetName() == a_component->GetName()) {
				// Debug print that the component we're trying to add already exists on this entity
				DEBUG *debug = DEBUG::getInstance();
				debug->printMessage("Component already exists on entity");
				return;
			}
		}

		/* Push back the component into the list */
		m_components.push_back(a_component);
	}

	void Entity::RemoveComponent(const char * a_name)
	{
		// Loop through the components list, look for component with a_name
		//std::vector<Component*>::iterator iter;
		//for (iter = m_components.begin(); iter != m_components.end(); ) {
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->GetName() == a_name) {
				m_components[i]->SetDestroyTrigger(true); // Set the component to be destroyed next iteration through the list
				return; // We're done with the operation
			}
		}
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
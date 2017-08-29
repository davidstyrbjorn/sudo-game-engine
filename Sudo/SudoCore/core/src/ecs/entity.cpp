#include"entity.h"
#include"../systems/world_system.h"
#include"../debug.h"

namespace sudo { namespace ecs {

	Entity::~Entity()
	{

	}

	Entity::Entity(char* a_name) : m_name(a_name) 
	{
		/* Adding the entity to the WorldSystem list */
		system::WorldSystem *world = system::WorldSystem::Instance();
		world->AddEntity(this);

		
	}

	void Entity::Update()
	{
		for (int i = 0; i < m_components.size(); i++) {

			// Check if component is up for being updated
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->Update();
			}

			// Remove component
			else if (m_components[i]->GetDestroyTrigger()) {
				/* Create iterator */
				std::vector<Component*>::iterator it;
				/* Iterate over the components list and delete */
				for (it = m_components.begin(); it != m_components.end(); ) {
					if ((*it)->GetDestroyTrigger()) {
						/* Found it, now delete it */
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
		/* Call start on all the components */
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->Start();
			}
		}

		/* Create the transform component */
		transform = new Transform();
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

		a_component->SetEntityHolder(this);

		/* Push back the component into the list */
		m_components.push_back(a_component);
	}

	void Entity::RemoveComponent(const char * a_name)
	{
		// Loop through the components list, look for component with a_name
		for (int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->GetName() == a_name) {
				m_components[i]->SetDestroyTrigger(true); // Set the component to be destroyed next iteration through the list
				return; // We're done with the operation
			}
		}
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
#include"entity.h"
#include"../systems/world_system.h"
#include"../debug.h"

namespace sudo { namespace ecs {

	Entity::~Entity()
	{
		for (std::vector< ecs::Component* >::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			delete (*it);
		}
		m_components.clear();
	}

	Entity::Entity(char* a_name) : m_name(a_name) 
	{
		/* Adding the entity to the WorldSystem list */
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		world->AddEntity(this);

		/* Create the transform component */
		transform = new Transform();
		transform->SetEntityHolder(this);
	}

	void Entity::Update()
	{
		/* Update the transform component */
		if (transform->GetComponentState() == ComponentState::ACTIVE) {
			transform->Update();
		}

		for (unsigned int i = 0; i < m_components.size(); i++) {

			// Check if component is up for being updated
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->Update();
			}
		}
	}

	void Entity::Start() 
	{
		transform->Start();

		/* Call start on all the components */
		for (unsigned int i = 0; i < m_components.size(); i++) {
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->Start();
			}
		}
	}

	void Entity::AddComponent(Component *a_component) 
	{
		/* Check if the component already exists */
		for (unsigned int i = 0; i < m_components.size(); i++) {
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

	void Entity::SetName(char* a_name)
	{
		m_name = a_name;
	}

	char* Entity::GetName() 
	{
		return m_name;
	}
	
} }
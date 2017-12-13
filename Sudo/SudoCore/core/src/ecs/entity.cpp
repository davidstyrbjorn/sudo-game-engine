#include"entity.h"
#include"../systems/world_system.h"
#include"../debug.h"

#include"transform_component.h"
#include"component.h"

namespace sudo { namespace ecs {

	Entity::~Entity()
	{
		for (std::vector< ecs::Component* >::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			delete (*it);
		}
		m_components.clear();
	}

	Entity::Entity()
	{
		/* Adding the entity to the WorldSystem list */
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		world->AddEntity(this);

		/* Create the transform component */
		transform = new Transform();
		transform->SetEntityHolder(this);

		/* Default active state */
		m_isActive = true;
		m_removeMe = false;
	}

	void Entity::Update(float deltaTime)
	{
		/* Update the transform component */
		if (transform->GetComponentState() == ComponentState::ACTIVE) {
			transform->Update(deltaTime);
		}

		for (unsigned int i = 0; i < m_components.size(); i++) {

			// Check if component is up for being updated
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->Update(deltaTime);
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

	void Entity::Awake()
	{
		transform->Awake();

		/* Call awake on all the components */
		for (unsigned int i = 0; i < m_components.size(); i++) {
			m_components[i]->Awake();
		}
	}

	Component* Entity::AddComponent(Component *a_component)
	{
		/* Set the components entity holder */
		a_component->SetEntityHolder(this);

		/* Push back the component into the list */
		m_components.push_back(a_component);

		/* Return the created component for the user to possibly store */
		return a_component;
	}
	
} }
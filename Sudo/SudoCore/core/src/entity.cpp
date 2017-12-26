#include"../include/ecs/entity.h"
#include"../include/systems/world_system.h"
#include"../include/debug.h"
#include"../include/graphics/renderable2d.h"

#include"../include/ecs/transform_component.h"
#include"../include/ecs/component.h"

namespace sudo { namespace ecs {

	Entity::~Entity()
	{
		for (std::vector< ecs::Component* >::iterator it = m_components.begin(); it != m_components.end(); ++it) {
			delete (*it);
		}
		m_components.clear();

		delete transform;
		// This line is not needed because m_renderableComponent is deleted when
		//delete m_renderableComponent;
	}

	void Entity::init()
	{
		/* Adding the entity to the WorldSystem list */
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		world->AddEntity(this);

		/* Create the transform component */
		transform = new Transform();
		transform->SetEntityHolder(this);

		/* This is a nullptr until the user adds one */
		m_renderableComponent = nullptr;

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

	void Entity::LateUpdate(float deltaTime)
	{
		for (unsigned int i = 0; i < m_components.size(); i++) {

			// Check if component is up for being updated
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->LateUpdate(deltaTime);
			}
		}
	}

	void Entity::Render()
	{
		for (unsigned int i = 0; i < m_components.size(); i++) {

			// Check if component is up for being updated
			if (m_components[i]->GetComponentState() == ComponentState::ACTIVE) { // Check if the component is active
				m_components[i]->Render();
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

		/* Check if a_component is of type renderable2d */
		graphics::Renderable2D *renderable = dynamic_cast<graphics::Renderable2D*>(a_component);
		if (renderable != nullptr) {
			m_renderableComponent = renderable;
		}

		/* Return the created component for the user to possibly store */
		return a_component;
	}

	graphics::Renderable2D * Entity::GetRenderableComponent() const
	{
		if (m_renderableComponent == nullptr) {
			DEBUG::getInstance()->printMessage("Entity has no renderable component attatched");
		}
		return m_renderableComponent;
	}

	void Entity::SetRenderableComponent(graphics::Renderable2D * a_renderable)
	{
		m_renderableComponent = a_renderable;
	}
	
} }
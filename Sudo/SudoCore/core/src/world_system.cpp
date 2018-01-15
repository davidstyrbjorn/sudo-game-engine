#include"../include/systems/world_system.h"

#include"../include/ecs/entity.h"

#include"../include/math/vector2.h"
#include"../include/math/vector3.h"

#include"../include/ecs/transform_component.h"
#include"../include/ecs/four_way_move_component.h"
#include"../include/ecs/box_collider2D.h"
#include"../include/ecs/sound_component.h"
#include"../include/ecs/sprite_component.h"
#include"../include/ecs/rectangle_component.h"

#include<assert.h>

namespace sudo { namespace sudo_system { 

	WorldSystem* WorldSystem::_instance = nullptr;

	WorldSystem* WorldSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new WorldSystem();

		return _instance;
	}

	void WorldSystem::Enable() 
	{
		m_isActive = true;
	}

	void WorldSystem::Disable() 
	{
		m_isActive = false;
	}

	void WorldSystem::CleanUp() 
	{
		for (std::vector< ecs::Entity* >::iterator it = m_entityList.begin(); it != m_entityList.end(); ++it) {
			delete (*it);
		}
		m_entityList.clear();
	}

	const std::vector<ecs::Entity*> WorldSystem::GetEntityList()
	{
		return m_entityList;
	}

	const std::vector<ecs::Entity*> WorldSystem::GetRenderableEntities()
	{
		std::vector<ecs::Entity*> returnVector;
		// Get every valid entity with a renderable component pushed into the local return vector
		for (int i = 0; i < m_entityList.size(); i++) {
			if (m_entityList[i]->GetRenderableComponent() != nullptr && m_entityList[i]->IsActive() && !m_entityList[i]->DestroyMe()) {
				returnVector.push_back(m_entityList[i]);
			}
		}
		return returnVector;
	}

	void WorldSystem::Update(float deltaTime)
	{
		if (m_isActive) {
			for (unsigned int i = 0; i < m_entityList.size(); i++) {
				if (m_entityList[i]->IsActive()) {
					m_entityList[i]->Update(deltaTime);
				}
			}

			std::vector<ecs::Entity*>::iterator it;
			for (it = m_entityList.begin(); it != m_entityList.end(); ) {
				if ((*it)->DestroyMe()) {
					delete *it;
					it = m_entityList.erase(it);
				}
				else {
					++it;
				}
			}
		}
	}

	void WorldSystem::LateUpdate(float deltaTime)
	{
		if (m_isActive) {
			for (unsigned int i = 0; i < m_entityList.size(); i++) {
				if (m_entityList[i]->IsActive()) {
					m_entityList[i]->LateUpdate(deltaTime);
				}
			}
		}
	}

	void WorldSystem::Render()
	{
		if (m_isActive) {
			for (unsigned int i = 0; i < m_entityList.size(); i++) {
				if (m_entityList[i]->IsActive()) {
					m_entityList[i]->Render();
				}
			}
		}
	}

	void WorldSystem::Start() 
	{
		for (unsigned int i = 0; i < m_entityList.size(); i++) {
			if(m_entityList[i]->IsActive())
				m_entityList[i]->Start();
		}
	}

	void WorldSystem::AddEntity(ecs::Entity *a_entityToAdd) 
	{
		m_entityList.push_back(a_entityToAdd);
	}

	void WorldSystem::RemoveEntity(ecs::Entity * a_entityToRemove)
	{
		a_entityToRemove->Destroy();
	}

	void WorldSystem::RemoveAllEntitiesWithID(const std::string& a_id)
	{
		for (int i = 0; i < m_entityList.size(); i++) {
			if (m_entityList[i]->GetID() == a_id) {
				m_entityList[i]->Destroy();
			}
		}
	}

	ecs::Entity & WorldSystem::CopyEntity(ecs::Entity * a_entityToCopy)
	{
		assert(a_entityToCopy != nullptr);

		// Create and name the component
		std::string dick = a_entityToCopy->GetID() + "(copy)";
		ecs::Entity *newEntity = new ecs::Entity(dick);

		// Get the list of components to immitate
		std::vector<ecs::Component*> componentsToCopy = a_entityToCopy->GetComponentList();

		// Transform component
		newEntity->transform->position = a_entityToCopy->transform->position;
		newEntity->transform->angle = a_entityToCopy->transform->angle;

		// Renderable Component
		if (a_entityToCopy->GetRenderableComponent() != nullptr)
		{
			if (a_entityToCopy->GetRenderableComponent()->getTID() == 0) {
				// Rectangle Component
				ecs::RectangleComponent* rectangleToCopy = static_cast<ecs::RectangleComponent*>(a_entityToCopy->GetRenderableComponent());
				if (rectangleToCopy != nullptr)
				{
					newEntity->AddComponent(new ecs::RectangleComponent((math::Vector2)rectangleToCopy->GetSize(), rectangleToCopy->GetColor()))->Start();
				}
			}
			else {
				// Sprite Component
				ecs::SpriteComponent* spriteToCopy = static_cast<ecs::SpriteComponent*>(a_entityToCopy->GetRenderableComponent());
				if (spriteToCopy != nullptr)
				{
					char* imagePath = spriteToCopy->GetSpriteImagePath();
					newEntity->AddComponent(new ecs::SpriteComponent(imagePath))->Start();
				}
			}
		}

		for (int i = 0; i < componentsToCopy.size(); i++)
		{
			bool _alreadyAddedComponent = false;

			ecs::BoxCollider2D* colliderToCopy = dynamic_cast<ecs::BoxCollider2D*>(componentsToCopy[i]);
			if (colliderToCopy != nullptr && !_alreadyAddedComponent) 
			{
				newEntity->AddComponent(new ecs::BoxCollider2D())->Start();
				_alreadyAddedComponent = true;
			}

			ecs::FourWayMoveComponent *fwmToCopy = dynamic_cast<ecs::FourWayMoveComponent*>(componentsToCopy[i]);
			if (fwmToCopy != nullptr && !_alreadyAddedComponent) 
			{
				newEntity->AddComponent(new ecs::FourWayMoveComponent(fwmToCopy->GetVelocity(), fwmToCopy->GetKeys("up"), fwmToCopy->GetKeys("down"), fwmToCopy->GetKeys("right"), fwmToCopy->GetKeys("left")))->Start();
				_alreadyAddedComponent = true;
			}

			ecs::SoundComponent *soundToCopy = dynamic_cast<ecs::SoundComponent*>(componentsToCopy[i]);
			if (soundToCopy != nullptr && !_alreadyAddedComponent)
			{
				printf("Copy of sound component not implemented");
				_alreadyAddedComponent = true;
			}
		}

		return *newEntity;
	}

	std::vector<ecs::Entity*> WorldSystem::GetEntitiesWithID(const std::string& a_id)
	{
		std::vector<ecs::Entity*> _list;
		for (ecs::Entity* temp : m_entityList) {
			if (temp->GetID() == a_id) {
				_list.push_back(temp);
			}
		}
		return _list;
	}

} }
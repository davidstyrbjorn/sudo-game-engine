#include"../include/systems/world_system.h"

#include"../include/ecs/entity.h"

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

	void WorldSystem::RemoveAllEntitiesWithID(const char* a_id)
	{
		for (int i = 0; i < m_entityList.size(); i++) {
			if (m_entityList[i]->GetID() == a_id) {
				m_entityList[i]->Destroy();
			}
		}
	}

	std::vector<ecs::Entity*> WorldSystem::GetEntitiesWithID(const char* a_id)
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
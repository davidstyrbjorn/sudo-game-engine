#include"world_system.h"

#include"../ecs/entity.h"

namespace sudo { namespace system { 

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

	void WorldSystem::Update()
	{
		if (m_isActive) {
			for (unsigned int i = 0; i < m_entityList.size(); i++) {
				m_entityList[i]->Update();
			}
		}
	}

	void WorldSystem::Start() 
	{
		if (m_isActive) {
			for (unsigned int i = 0; i < m_entityList.size(); i++) {
				m_entityList[i]->Start();
			}
		}
	}

	void WorldSystem::AddEntity(ecs::Entity *a_entityToAdd) 
	{
		m_entityList.push_back(a_entityToAdd);
	}
} }
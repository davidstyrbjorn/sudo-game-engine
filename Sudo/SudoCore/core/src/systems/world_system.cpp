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

	void WorldSystem::Update()
	{
		if (m_isActive) {
			for (int i = 0; i < m_entityList.size(); i++) {
				m_entityList[i]->Update();
			}
		}
	}

	void WorldSystem::Start() 
	{
		if (m_isActive) {
			for (int i = 0; i < m_entityList.size(); i++) {
				m_entityList[i]->Start();
			}
		}
	}

	void WorldSystem::AddEntity(ecs::Entity *a_entityToAdd) 
	{
		m_entityList.push_back(a_entityToAdd);
	}

	void WorldSystem::RemoveEntity(const char* a_name, unsigned char a_deleteAll) 
	{
		// Remove entity.a_name from the list
	}
} }
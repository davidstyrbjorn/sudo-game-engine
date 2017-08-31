#include "render_system.h"

namespace sudo { namespace system {

	RenderSystem* RenderSystem::_instance = nullptr;

	void RenderSystem::Update() 
	{

	}

	void RenderSystem::Start() 
	{

	}

	void RenderSystem::Enable() 
	{

	}

	void RenderSystem::Disable() 
	{

	}

	void RenderSystem::CleanUp() 
	{

	}

	RenderSystem * sudo::system::RenderSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new RenderSystem();

		return _instance;
	}

} } 

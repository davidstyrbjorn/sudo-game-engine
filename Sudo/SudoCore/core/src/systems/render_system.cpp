#include "render_system.h"
#include"../../sudo.h"

namespace sudo { namespace system {

	RenderSystem* RenderSystem::_instance = nullptr;

	void RenderSystem::Update() 
	{
		// Iterate through the m_renderList and render each renderable2D inside
		
	}

	void RenderSystem::Start()
	{
		m_shader = new graphics::Shader("C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shader_vertex.txt", "C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shader_fragment.txt");
	}

	void RenderSystem::CleanUp() 
	{
		//m_renderList.clear();
	}

	void RenderSystem::Draw(graphics::Renderable2D *a_shape)
	{
		m_renderList.push_back(a_shape);
	}

	RenderSystem * sudo::system::RenderSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new RenderSystem();

		return _instance;
	}

} } 

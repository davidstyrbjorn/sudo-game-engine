#include "render_system.h"
#include"../../sudo.h"
#include"../../gl_include.h"

namespace sudo { namespace system {

	RenderSystem* RenderSystem::_instance = nullptr;

	void RenderSystem::Update() 
	{
		// Iterate through the m_renderList and render each renderable2D inside
		while (!m_renderList.empty()) {
			graphics::Renderable2D *renderObject = m_renderList.front();
			
			// Bind stuff and set model_matrix accordingly
			m_shader->setUniformMatrix4x4("model_matrix", math::Matrix4x4::Translation(renderObject->GetEntityTransform()->position));
			renderObject->bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			renderObject->unbind();
			m_renderList.pop_front();
		}
	}

	void RenderSystem::Start()
	{
		glewInit();
		glewExperimental = true;

		m_shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shader_fragment.txt");
		m_shader->enable();
		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, 800, 600, 0, -1, 1));
	}
	
	void RenderSystem::Draw(graphics::Renderable2D *a_shape)
	{
		m_renderList.push_back(a_shape);
	}

	void RenderSystem::CleanUp()
	{
		//m_renderList.clear();
	}

	RenderSystem * sudo::system::RenderSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new RenderSystem();

		return _instance;
	}

} } 

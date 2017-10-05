#include "render_system.h"
#include"../../sudo.h"
#include"../../gl_include.h"

namespace sudo { namespace sudo_system {

	RenderSystem* RenderSystem::_instance = nullptr;

	void RenderSystem::Update() 
	{
		// Iterate through the m_renderList and render each renderable2D inside
		while (!m_renderList.empty()) {
			graphics::Renderable2D *renderObject = m_renderList.front();
			
			/* Is it a shape or a sprite using a texture? The Shader HAVE to know this */
			if (renderObject->m_type == sudo::RenderableType::SHAPE) {
				m_shader->setUniform1f("texture_mode", 0);
			}
			if (renderObject->m_type == sudo::RenderableType::SPRITE) {
				m_shader->setUniform1f("texture_mode", 1);
			}

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

		m_shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_fragment.txt");
		m_shader->enable();
		m_shader->setUniform1f("myTexture", 0);

		sudo_system::SettingsSystem* settings = sudo_system::SettingsSystem::Instance();
		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, settings->GetWindowSize().getX(), settings->GetWindowSize().getY(), 0, -1, 1));
	}

	void RenderSystem::CleanUp()
	{
		//m_renderList.clear();
	}

	RenderSystem * sudo::sudo_system::RenderSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new RenderSystem();

		return _instance;
	}

} } 

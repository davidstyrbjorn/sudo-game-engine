#include"batch_render_system.h"
#include"../../sudo.h"

#include"../../gl_include.h"

namespace sudo { namespace sudo_system { 

	BatchRendererSystem* BatchRendererSystem::_instance = nullptr;
	BatchRendererSystem * BatchRendererSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new BatchRendererSystem();
		return _instance;
	}

	BatchRendererSystem::BatchRendererSystem()
	{
		// Create and bind buffer
		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

		// Structure the buffer layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), nullptr); // Vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<void*>(offsetof(graphics::VertexData, color))); // Vertex color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<void*>(offsetof(graphics::VertexData, uvCoord))); // Vertex texture coordinates
		glEnableVertexAttribArray(2);
	}

	void BatchRendererSystem::Start()
	{
		m_shader = new graphics::Shader("C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_vertex.txt", "C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_fragment.txt");
		m_shader->enable();
		m_shader->setUniform1f("myTexture", 0);

		sudo_system::SettingsSystem* settings = sudo_system::SettingsSystem::Instance();
		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, settings->GetWindowSize().x, settings->GetWindowSize().y, 0, -1, 1));
	}

	void BatchRendererSystem::Begin()
	{
		// Reset primitive count
		m_primitiveCount = 0;

		// Bind and reset buffer data
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	}

	void BatchRendererSystem::Submit(graphics::VertexData *a_vertices)
	{
		// Offset up to the current empty border 
		GLintptr initialOffset = (m_primitiveCount * (sizeof(graphics::VertexData) * 3));
		// Add data at this point, size will be three vertices
		glBufferSubData(GL_ARRAY_BUFFER, initialOffset, sizeof(graphics::VertexData) * 3, a_vertices);
		// Increment the primitive count
		m_primitiveCount++;
	}

	void BatchRendererSystem::Flush()
	{
		if(m_primitiveCount != 0)
			glDrawArrays(GL_TRIANGLES, 0, m_primitiveCount * 3);

		// Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRendererSystem::CleanUp()
	{

	}

} } 
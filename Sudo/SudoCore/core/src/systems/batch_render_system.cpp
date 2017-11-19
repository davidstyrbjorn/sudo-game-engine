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

	}

	void BatchRendererSystem::Start()
	{
		glewInit();
		glewExperimental = true;

		m_shader = new graphics::Shader("C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_vertex.txt", "C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_fragment.txt");
		m_shader->enable();
		m_shader->setUniform1f("myTexture", 0);

		sudo_system::SettingsSystem* settings = sudo_system::SettingsSystem::Instance();
		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, settings->GetWindowSize().x, settings->GetWindowSize().y, 0, -1, 1));


		// =============== Quad ===================
		m_quadVertexArrayBuffer = new graphics::VertexArrayBuffer();
		m_quadVertexArrayBuffer->bind();

		// Create and bind buffer
		glGenBuffers(1, &m_quadBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_quadBuffer);
		// Structure the buffer layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), nullptr); // Vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<void*>(offsetof(graphics::VertexData, color))); // Vertex color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<void*>(offsetof(graphics::VertexData, uvCoord))); // Vertex texture coordinates
		glEnableVertexAttribArray(2);

		// Quad index buffer
		int m_indicesOffset = 0;
		uint m_indices[INDICES_COUNT];
		for (int i = 0; i < INDICES_COUNT; i += 6) 
		{
			m_indices[i + 0] =	m_indicesOffset + 0;
			m_indices[i + 1] =	m_indicesOffset + 1;
			m_indices[i + 2] =	m_indicesOffset + 2;
				
			m_indices[i + 3] =	m_indicesOffset + 2;
			m_indices[i + 4] =	m_indicesOffset + 3;
			m_indices[i + 5] =	m_indicesOffset + 0;

			m_indicesOffset += 4;
		}
		m_quadIndexBuffer = new graphics::IndexBuffer(m_indices,  sizeof(m_indices));
	}

	void BatchRendererSystem::Begin()
	{
		// Reset primitive count
		m_quadCount = 0;

		// Bind and reset buffer data
		m_quadVertexArrayBuffer->bind();
		glBindBuffer(GL_ARRAY_BUFFER, m_quadBuffer);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	}

	void BatchRendererSystem::Submit(graphics::Renderable2D *a_primitive, uint a_vertexCount)
	{
		if (a_vertexCount == 4) 
		{
			m_quadVertexArrayBuffer->bind();
			glBindBuffer(GL_ARRAY_BUFFER, m_quadBuffer);
			// Offset up to the current empty point in the buffer
			GLintptr initialOffset = m_quadCount*(sizeof(graphics::VertexData) * 4);
			glBufferSubData(GL_ARRAY_BUFFER, initialOffset, sizeof(graphics::VertexData) * 4, a_primitive->GetPrimitiveData().data());

			// Increment the primitive count
			m_quadCount++;
		}
	}

	void BatchRendererSystem::Flush()
	{
		// Draw call
		if (m_quadCount != 0) {
			m_quadVertexArrayBuffer->bind();
			m_quadIndexBuffer->bind();
			glBindBuffer(GL_ARRAY_BUFFER, m_quadBuffer);
			glDrawElements(GL_TRIANGLES, 6 * m_quadCount, GL_UNSIGNED_INT, 0);
		}

		// Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRendererSystem::CleanUp()
	{
		glDeleteBuffers(1, &m_quadBuffer);

		delete m_quadIndexBuffer;
		delete m_quadVertexArrayBuffer;
	}

} } 
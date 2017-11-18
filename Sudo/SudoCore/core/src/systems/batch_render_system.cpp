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

		m_vertexArrayBuffer = new graphics::VertexArrayBuffer();
		m_vertexArrayBuffer->bind();

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
										  
		m_indicesOffset = 0;
		
		/*
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
		*/
		
		m_indexBuffer = new graphics::IndexBuffer(m_indices.data(), m_indices.size() * sizeof(unsigned int));
		m_indexBuffer->setData(nullptr, 0);

		m_vertexArrayBuffer->unbind();
	}

	void BatchRendererSystem::Begin()
	{
		// Bind vertex array
		m_vertexArrayBuffer->bind();

		m_indicesOffset = 0;
		// Reset primitive count
		m_primitiveCount = 0;

		// Bind and reset buffer data
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	}

	void BatchRendererSystem::Submit(graphics::VertexData *a_vertices, uint a_vertexCount)
	{
		if (a_vertexCount == 3) 
		{
			m_indices.push_back(m_indicesOffset + 0);
			m_indices.push_back(m_indicesOffset + 1);
			m_indices.push_back(m_indicesOffset + 2);

			m_indicesOffset = 3;
		}
		if (a_vertexCount == 4) 
		{
			m_indices.push_back(m_indicesOffset + 0);
			m_indices.push_back(m_indicesOffset + 1);
			m_indices.push_back(m_indicesOffset + 2);

			m_indices.push_back(m_indicesOffset + 2);
			m_indices.push_back(m_indicesOffset + 3);
			m_indices.push_back(m_indicesOffset + 0);

			m_indicesOffset = 4;
		}

		// Offset up to the current empty point in the buffer
		GLintptr initialOffset = m_primitiveCount*(sizeof(graphics::VertexData) * a_vertexCount);
		glBufferSubData(GL_ARRAY_BUFFER, initialOffset, sizeof(graphics::VertexData) * a_vertexCount, a_vertices);
		
		// Increment the primitive count
		m_primitiveCount++;
	}

	void BatchRendererSystem::Flush()
	{			
		m_indexBuffer->setData(m_indices.data(), m_indices.size() * sizeof(uint));
		m_indices.clear();

		if(m_primitiveCount != 0) 
			glDrawElements(GL_TRIANGLES, 6*m_primitiveCount, GL_UNSIGNED_INT, 0);

		// Unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRendererSystem::CleanUp()
	{
		glDeleteBuffers(1, &m_buffer);

		delete m_indexBuffer;
		delete m_vertexArrayBuffer;
	}

} } 
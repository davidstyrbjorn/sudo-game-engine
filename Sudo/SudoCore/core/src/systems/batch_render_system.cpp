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

		m_shader = new graphics::Shader("C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\unlit_shader_vertex.txt", "C:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\shader_fragment.txt");
		m_shader->enable();

		int texIds[] = { 0,1,2,3,4,5,6,7,8,9 };
		m_shader->setUniform1iv("textures", 10, texIds);

		sudo_system::SettingsSystem* settings = sudo_system::SettingsSystem::Instance();
		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, settings->GetWindowSize().x, settings->GetWindowSize().y, 0, -1, 1));

		// =============== START ===================
		m_vertexArrayBuffer = new graphics::VertexArrayBuffer();
		m_vertexArrayBuffer->bind();

		// Create and bind buffer
		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
		glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
		// Structure the buffer layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), nullptr); // Vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::VertexData, color))); // Vertex color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::VertexData, uv))); // Vertex texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(graphics::VertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::VertexData, tid)));
		glEnableVertexAttribArray(3);

		// index buffer
#if USE_INDEX_BUFFER
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
		m_indexBuffer = new graphics::IndexBuffer(m_indices,  sizeof(m_indices));
#endif
	}

	void BatchRendererSystem::Begin()
	{
		// Reset primitive count
		m_primitiveCount = 0;

		// Only map the buffer if the renderer is active
		if (m_isActive) {
			// Bind and reset buffer data
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
			m_mapBuffer = (graphics::VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}
	}

	void BatchRendererSystem::Submit(graphics::Renderable2D *a_primitive)
	{
		// Only submit data if the renderer is active
		if (m_isActive) {
			// Texture
			const uint tid = a_primitive->getTID();
			float ts = 0.0f; // texture slot
			if (tid > 0)
			{
				bool found = false;
				for (int i = 0; i < m_textureSlots.size(); i++)
				{
					if (m_textureSlots[i] == tid)
					{
						found = true;
						ts = (float)(i + 1);
						break;
					}
				}

				if (!found)
				{
					if (m_textureSlots.size() >= 32) {
						End();
						Flush();
						Begin();
					}
					m_textureSlots.push_back(tid);
					ts = (float)(m_textureSlots.size());
				}
			}

			const math::Vector3 &_position = a_primitive->GetEntityTransform()->position;
			const math::Vector2 &_size = a_primitive->GetSize();
			const math::Vector4 &_color = a_primitive->GetColor();

			m_mapBuffer->pos = _position;
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(0, 0);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			m_mapBuffer->pos = math::Vector3(_position.x, _position.y + _size.y, 0);
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(0, 1);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			m_mapBuffer->pos = math::Vector3(_position.x + _size.x, _position.y + _size.y, 0);
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(1, 1);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			m_mapBuffer->pos = math::Vector3(_position.x + _size.x, _position.y, 0);
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(1, 0);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// This method won't work with texture arrays implementation
			/*
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
			// Offset up to the current empty point in the buffer
			GLintptr initialOffset = m_primitiveCount*(sizeof(graphics::VertexData) * a_vertexCount);
			glBufferSubData(GL_ARRAY_BUFFER, initialOffset, sizeof(graphics::VertexData) * a_vertexCount, a_primitive->GetPrimitiveData().data());
			*/

			// Increment the primitive count
			m_primitiveCount++;
		}
	}

	void BatchRendererSystem::Flush()
	{
		if (m_primitiveCount != 0) {
#if USE_INDEX_BUFFER
			// Bind the textures
			for (int i = 0; i < m_textureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			m_indexBuffer->bind();
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

			// Draw call
			glDrawElements(GL_TRIANGLES, 6 * m_primitiveCount, GL_UNSIGNED_INT, 0);
#else
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
			glDrawArrays(GL_TRIANGLES, 0, 6 * m_primitiveCount);
#endif
		}
	}

	void BatchRendererSystem::End()
	{
		// Empty the buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void BatchRendererSystem::CleanUp()
	{
		m_isActive = false;
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glDeleteBuffers(1, &m_buffer);

#if USE_INDEX_BUFFER
		delete m_indexBuffer;
#endif
		delete m_vertexArrayBuffer;
	}

} } 
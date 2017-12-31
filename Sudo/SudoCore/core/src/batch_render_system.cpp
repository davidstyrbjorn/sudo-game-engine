#include"../include/systems/batch_render_system.h"
#include"../include/gl_include.h"

#include"../include/graphics/shader.h"
#include"../include/graphics/buffers/index_buffer.h"
#include"../include/graphics/buffers/vertex_array_buffer.h"
#include"../include/graphics/renderable2d.h"
#include"../include/graphics/texture.h"

#include"../include/systems/settings_system.h"
#include"../include/systems/world_system.h"

#include"../include/math/mat4.h"
#include"../include/math/color.h"
#include"../include/math/vector3.h"
#include"../include/math/math.h"

#include"../include/ecs/transform_component.h"
#include"../include/ecs/rectangle_component.h"
#include"../include/ecs/sprite_component.h"
#include"../include/ecs/entity.h"

#include<algorithm>

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
		m_worldSystem = WorldSystem::Instance();
		m_settingsSystem = SettingsSystem::Instance();
	}

	void BatchRendererSystem::Start()
	{
		glewInit();
		glewExperimental = true;

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Creating shader 
		const char* vertex = "#version 330 core \n layout(location = 0) in vec3 in_pos; \n layout(location = 1) in vec4 in_color; \n layout(location = 2) in vec2 in_texCoords; \n layout(location = 3) in float tid;  \n uniform mat4 projection_matrix;  \n uniform mat4 view_matrix = mat4(1.0);  \n uniform mat4 model_matrix = mat4(1.0);  \n out vec4 out_color;  \n out vec2 out_texCoords;  \n out float out_tid;  \n void main()  \n {  \n gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_pos.x, in_pos.y, in_pos.z, 1.0);  \n out_texCoords = in_texCoords;  \n out_color = in_color;  \n out_tid = tid;  \n }  \n";
		const char* fragment = "#version 330 core \n in vec4 out_color; \n in vec2 out_texCoords; \n in float out_tid; \n uniform sampler2D textures[32]; \n void main() \n { \n vec4 texColor = out_color; \n if (out_tid > 0.0) { \n int tid = int(out_tid - 0.5); \n texColor = texture(textures[tid], out_texCoords); \n } \n gl_FragColor = texColor; \n if (gl_FragColor.a < 0.1) { \n discard; \n } \n } \n";
		m_shader = new graphics::Shader(vertex, fragment, 1);
		//m_shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\shader_fragment.txt");
		m_shader->enable();

		int texIds[] = { 0,1,2,3,4,5,6,7,8,9 };
		m_shader->setUniform1iv("textures", 10, texIds);

		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(
			0, 
			sudo_system::SettingsSystem::Instance()->GetWindowSize().x, 
			sudo_system::SettingsSystem::Instance()->GetWindowSize().y,
			0, 
			NEAR, FAR));
		m_shader->disable();

		// OpenGL starts here
		glGenVertexArrays(1, &m_quadVAO);
		glBindVertexArray(m_quadVAO);

		// Create and bind quad buffer
		glGenBuffers(1, &m_quadVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
		glBufferData(GL_ARRAY_BUFFER, QUAD_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		// Structure the quad buffer layout - bound to m_vertexArray
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::QuadVertexData), nullptr); // Vertex position
		glEnableVertexAttribArray(0);									 
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(graphics::QuadVertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::QuadVertexData, color))); // Vertex color
		glEnableVertexAttribArray(1);									 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(graphics::QuadVertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::QuadVertexData, uv))); // Vertex texture coordinates
		glEnableVertexAttribArray(2);									 
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(graphics::QuadVertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::QuadVertexData, tid)));
		glEnableVertexAttribArray(3);

		// quad index buffer
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

		//glBindVertexArray(0);

		// Triangle VAO
		//glGenVertexArrays(1, &m_triangleVAO);
		//glBindVertexArray(m_triangleVAO);
		//
		//// Triangle VBO
		//glGenBuffers(1, &m_triangleVBO);
		//glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
		//glBufferData(GL_ARRAY_BUFFER, TRIANGLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
		//
		//// Structure the quad buffer layout - bound to m_triangleVAO
		//glEnableVertexAttribArray(1);
		//glEnableVertexAttribArray(0);
		////glEnableVertexAttribArray(2);
		////glEnableVertexAttribArray(3);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(graphics::TriangleVertexData), nullptr); // Vertex position
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(graphics::TriangleVertexData), reinterpret_cast<GLvoid*>(offsetof(graphics::TriangleVertexData, color))); // Vertex color
	}

	void BatchRendererSystem::Begin()
	{
		// Reset primitive count
		m_quadCount = 0;
		m_triangleCount = 0;

		// Only map the buffer if the renderer is active
		if (m_isActive) {
			// Bind and reset triangle buffer data
			//glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
			//glBufferData(GL_ARRAY_BUFFER, TRIANGLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

			// Bind and reset quad buffer data
			glBindVertexArray(m_quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
			m_mapBuffer = (graphics::QuadVertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}
	}

	void BatchRendererSystem::Submit(graphics::Renderable2D *a_primitive, graphics::Renderable2D *a_primitive2, graphics::Renderable2D *a_primitive3)
	{
		if (a_primitive  != nullptr && a_primitive->GetEntityTransform()->GetEntityHolder()->IsActive())  _Submit(a_primitive);
		if (a_primitive2 != nullptr && a_primitive2->GetEntityTransform()->GetEntityHolder()->IsActive()) _Submit(a_primitive2);
		if (a_primitive3 != nullptr && a_primitive3->GetEntityTransform()->GetEntityHolder()->IsActive()) _Submit(a_primitive3);
	}

	void BatchRendererSystem::_Submit(graphics::Renderable2D *a_primitive)
	{
		// Only submit data if the renderer is active and we have space for the primitive
		if (m_isActive && (m_quadCount + m_trianglesToRender.size()) < MAX_PRIMITIVES) 
		{
			// Rectangles and sprties
			if (a_primitive->GetPointCount() == 4) {
				m_quadsToRender.push_back(a_primitive);
			}
			// Triangles
			if (a_primitive->GetPointCount() == 3) {
				m_trianglesToRender.push_back(a_primitive);
			}
		}
	}

	static bool layerCompare(graphics::Renderable2D *_1, graphics::Renderable2D *_2) {
		return (_1->GetEntityTransform()->position.z > _2->GetEntityTransform()->position.z);
	}

	void BatchRendererSystem::PrepareQuad()
	{
		if(m_quadsToRender.size() > 1)
			std::sort(m_quadsToRender.begin(), m_quadsToRender.end(), layerCompare);

		glBindVertexArray(m_quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
		// Rectangles and sprites
		while (!m_quadsToRender.empty()) 
		{
			// Get the primitive to be rendered
			graphics::Renderable2D* a_primitive = m_quadsToRender.back();

			// Texture
			const uint tid = a_primitive->getTID();
			float ts = 0.0f; // texture slot
			ts = GetTextureSlot(tid);

			// Clamp it to 0-1 for the shader
			const math::Color &_color = a_primitive->GetColor() / 255;

			// Vertex 1
			m_mapBuffer->pos = a_primitive->GetPrimitivePoints()[0];
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(0, 0);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Vertex 2
			m_mapBuffer->pos = a_primitive->GetPrimitivePoints()[1];
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(0, 1);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Vertex 3
			m_mapBuffer->pos = a_primitive->GetPrimitivePoints()[2];
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(1, 1);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Vertex 4
			m_mapBuffer->pos = a_primitive->GetPrimitivePoints()[3];
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(1, 0);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Pop the front of the deque
			m_quadsToRender.pop_back();
			m_quadCount++;
		}
	}

	void BatchRendererSystem::PrepareTriangle()
	{
		glBindVertexArray(m_triangleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
		while (!m_trianglesToRender.empty())
		{
			// Get the primitive to be rendered
			graphics::Renderable2D* a_primitive = m_trianglesToRender.front();
			const math::Color color = a_primitive->GetColor() / 255;

			graphics::TriangleVertexData data[] = {
				{ a_primitive->GetPrimitivePoints()[0], color },
				{ a_primitive->GetPrimitivePoints()[1], color },
				{ a_primitive->GetPrimitivePoints()[2], color }
			};

			glBufferSubData(GL_ARRAY_BUFFER, m_triangleCount * (sizeof(graphics::TriangleVertexData) * 3), sizeof(data), data);

			// Pop the front of the deque 
			m_trianglesToRender.pop_front();
			m_triangleCount++;
		}
	}

	void BatchRendererSystem::Flush()
	{
		// Enable shader
		m_shader->enable();

		if (m_quadCount != 0) {
			// Bind 
			glBindVertexArray(m_quadVAO);
			for (int i = 0; i < m_textureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}
			m_indexBuffer->bind();
			glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);

			// Draw call
			glDrawElements(GL_TRIANGLES, 6 * m_quadCount, GL_UNSIGNED_INT, 0);
		}
		/*
		if (m_triangleCount != 0) {
			// Bind
			glBindVertexArray(m_triangleVAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);

			// Draw call 
			glDrawArrays(GL_TRIANGLES, 0, 3 * m_triangleCount);
		}
		*/
	}

	void BatchRendererSystem::End()
	{
		// Empty the buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);

		// Unbind
		m_indexBuffer->unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void BatchRendererSystem::Update(float deltaTime)
	{
		if (m_settingsSystem->DoAutoRender()) {
			// This code auto renders every entity which has a renderable2D component 
			for (int i = 0; i < m_worldSystem->GetEntityList().size(); i++) {
				graphics::Renderable2D *temp = m_worldSystem->GetEntityList()[i]->GetRenderableComponent();
				if (temp != nullptr) {
					this->Submit(temp);
				}
			}
		}
	}

	float BatchRendererSystem::GetTextureSlot(int a_textureID) 
	{
		float _ts = 0.0f;
		if (a_textureID > 0)
		{
			bool found = false;
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == a_textureID)
				{
					found = true;
					_ts = (float)(i + 1);
					break;
				}
			}

			if (!found)
			{
				// GL_TEXTURE0 -> GL_TEXTURE32
				if (m_textureSlots.size() >= 32) {
					End();
					Flush();
					Begin();
				}
				m_textureSlots.push_back(a_textureID);
				_ts = (float)(m_textureSlots.size());
			}
		}

		return _ts;
	}

	void BatchRendererSystem::CleanUp()
	{
		m_isActive = false;
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glDeleteBuffers(1, &m_quadVBO);
		glDeleteBuffers(1, &m_triangleVBO);

		delete m_indexBuffer;
		glDeleteVertexArrays(1, &m_quadVAO);
		glDeleteVertexArrays(1, &m_triangleVAO);
	}

} } 
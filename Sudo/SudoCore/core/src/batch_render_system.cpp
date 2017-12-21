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
			-1, 1));
		m_shader->disable();

		// =============== START ===================
		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

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
			glBindVertexArray(m_vertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

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
					// GL_TEXTURE0 -> GL_TEXTURE32
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
			// Clamp it to 0-1 for the shader
			const math::Color &_color = a_primitive->GetColor()/255;
			// All the vertex positions
			math::Vector3 pos1, pos2, pos3, pos4;

			// Rotation calculation
			float angle = a_primitive->GetEntityTransform()->angle;
			float angleInRads = angle * DEG2RAD;

			// cx, cy - center for the rectangle
			float cx = a_primitive->GetEntityTransform()->position.x + (a_primitive->GetSize().x / 2);
			float cy = a_primitive->GetEntityTransform()->position.y + (a_primitive->GetSize().y / 2);

			// Vertex 1 rotation
			// Translate point to the origin
			float tempX = _position.x - cx;
			float tempY = _position.y - cy;
			// apply rotation
			float rotatedX = tempX*cos(angleInRads) - tempY*sin(angleInRads);
			float rotatedY = tempX*sin(angleInRads) + tempY*cos(angleInRads);
			pos1 = math::Vector3(rotatedX + cx, rotatedY + cy, 0);

			// Vertex 2 rotation
			// Translate point to the origin
			tempX = _position.x - cx;
			tempY = (_position.y + _size.y) - cy;
			// apply rotation
			rotatedX = tempX*cos(angleInRads) - tempY*sin(angleInRads);
			rotatedY = tempX*sin(angleInRads) + tempY*cos(angleInRads);
			pos2 = math::Vector3(rotatedX + cx, rotatedY + cy, 0);

			// Vertex 3 rotation
			// Translate point to the origin
			tempX = (_position.x + _size.x) - cx;
			tempY = (_position.y + _size.y) - cy;
			// apply rotation
			rotatedX = tempX*cos(angleInRads) - tempY*sin(angleInRads);
			rotatedY = tempX*sin(angleInRads) + tempY*cos(angleInRads);
			pos3 = math::Vector3(rotatedX + cx, rotatedY + cy, 0);

			// Vertex 4 rotation
			// Translate point to the origin
			tempX = (_position.x + _size.x) - cx;
			tempY = _position.y - cy;
			// apply rotation
			rotatedX = tempX*cos(angleInRads) - tempY*sin(angleInRads);
			rotatedY = tempX*sin(angleInRads) + tempY*cos(angleInRads);
			pos4 = math::Vector3(rotatedX + cx, rotatedY + cy, 0);

			// ============================================================ //
			// ================= Update the actual buffer ================= //
			// ============================================================ //

			// Vertex 1
			m_mapBuffer->pos = pos1;
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(0, 0);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Vertex 2
			m_mapBuffer->pos = pos2;
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(0, 1);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Vertex 3
			m_mapBuffer->pos = pos3;
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(1, 1);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Vertex 4
			m_mapBuffer->pos = pos4;
			m_mapBuffer->color = _color;
			m_mapBuffer->uv = math::Vector2(1, 0);
			m_mapBuffer->tid = ts;
			m_mapBuffer++;

			// Increment the primitive count
			m_primitiveCount++;
		}
	}

	void BatchRendererSystem::Flush()
	{
		if (m_primitiveCount != 0) {
#if USE_INDEX_BUFFER
			// Enable this shader
			m_shader->enable();
			// Bind the vertex array
			glBindVertexArray(m_vertexArray);
			// Bind the textures
			for (int i = 0; i < m_textureSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}
			m_indexBuffer->bind();
			glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

			// Draw call
			glDrawElements(GL_TRIANGLES, 6 * m_primitiveCount, GL_UNSIGNED_INT, 0);

			// Unbind
			glBindVertexArray(0);
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
		glDeleteVertexArrays(1, &m_vertexArray);
	}

} } 
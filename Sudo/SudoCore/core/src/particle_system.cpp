#include"../include/systems/particle_system.h"
#include"../include/gl_include.h"

#include"../include/math/mat4.h"
#include"../include/math/vector3.h"
#include"../include/math/vector2.h"
#include"../include/math/color.h"

#include"../include/systems/settings_system.h"

#include"../include/graphics/particle.h"
#include"../include/graphics/buffers/index_buffer.h" 
#include"../include/graphics/shader.h" 

namespace sudo { namespace sudo_system { 

struct ParticleVertexData {
	ParticleVertexData(const math::Vector2& a_pos, const math::Color& a_color)
	{
		pos = a_pos;
		color = a_color;
	}

	math::Vector2 pos;
	math::Color color;
};

} } 

#define PARTICLE_SIZE sizeof(ParticleVertexData) * 4
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES

#define INDICES_COUNT 6*MAX_PARTICLES

namespace sudo { namespace sudo_system {
	
	ParticleSystem* ParticleSystem::_instance = nullptr;

	ParticleSystem::ParticleSystem() 
	{
	}

	ParticleSystem * ParticleSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new ParticleSystem();
		return _instance;
	}

	void ParticleSystem::Toggle()
	{
		m_isActive = !m_isActive;
		if (m_isActive)
			Enable();
		else
			Disable();
	}

	void ParticleSystem::Enable()
	{
		m_isActive = true;
	}

	void ParticleSystem::Disable()
	{
		m_isActive = false;

		// Initalize particle array
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (m_particlePool[i] != nullptr)
				delete m_particlePool[i];

			m_particlePool[i] = new graphics::Particle();
			m_particlePool[i]->disable();
		}
		m_particleCount = 0;
	}

	void ParticleSystem::Start()
	{
		glewInit();
		glewExperimental = true;
		
		// Initalize particle array
		for (int i = 0; i < MAX_PARTICLES; i++) {
			m_particlePool[i] = new graphics::Particle();
			m_particlePool[i]->disable();
		}
		m_particleCount = 0;

		// Creating the shader
		const char *vertex = "#version 330 core \n layout(location = 0) in vec2 in_pos; \n layout(location = 1) in vec4 in_color; \n uniform mat4 projection_matrix; \n uniform mat4 view_matrix = mat4(1.0); \n uniform mat4 model_matrix = mat4(1.0); \n out vec4 out_color; \n void main() { \n gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_pos.x, in_pos.y, 0, 1.0); \n out_color = in_color; \n }";
		const char* fragment = "#version 330 core \n in vec4 out_color; \n void main() \n { \n gl_FragColor = out_color; \n }";
		m_shader = new graphics::Shader(vertex, fragment, 1);
		//m_shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\particle_shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\particle_shader_fragment.txt");
		m_shader->enable();

		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(
			0,
			sudo_system::SettingsSystem::Instance()->GetWindowSize().x,
			sudo_system::SettingsSystem::Instance()->GetWindowSize().y,
			0,
			-1, 1));
		m_shader->disable();

		// Set up the rendering buffer
		setUpVAO_VBO();
	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (m_particlePool[i]->m_active && m_isActive) {
				m_particlePool[i]->update(deltaTime);
			}
		}
	}

	void ParticleSystem::Begin()
	{
		m_particleCount = 0;
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (m_particlePool[i]->m_active) {
				m_particleCount++;
			}
		}

		// Reset
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, PARTICLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	}

	void ParticleSystem::Submit(math::Vector3 a_spawnPosition, 
		math::Vector2 a_particleSize, 
		math::Color a_particleColor, 
		uint a_lifeTime, 
		math::Vector2 a_velocity, 
		ParticleConfiguration a_config)
	{
		if (m_particleCount < MAX_PARTICLES && m_isActive) 
		{
			m_particlePool[m_particleCount]->init(math::Vector2(a_spawnPosition.x, a_spawnPosition.y), a_particleSize, a_particleColor, a_velocity, a_lifeTime);
			// Configuration
			m_particlePool[m_particleCount]->m_doAlphaBlend = a_config.DoFade;
			m_particlePool[m_particleCount]->m_gravitySimulated = a_config.GravitySimulated;
			m_particlePool[m_particleCount]->m_gravityScale = a_config.GravityScale;

			m_particleCount++;
		}
	}

	void ParticleSystem::Flush()
	{
		// Draw all the particles inside m_particlesToRender
		if (m_particleCount != 0 && m_isActive) {

			// Remove all dead particles before rendering
			disableDeadParticles();
			// Enable the particle shader
			m_shader->enable();
			// Bind
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_indexBuffer->bind();

			// Add all the particles from m_particlesToDraw list to the buffer
			int count = 0;
			for (int i = 0; i < MAX_PARTICLES; i++) {
				if (m_particlePool[i]->m_active) {
					const math::Vector2& position = m_particlePool[i]->m_position;
					const math::Vector2& size = m_particlePool[i]->m_size;
					const math::Color&   color = m_particlePool[i]->m_color/255;

					// This is to be pushed into the buffer
					ParticleVertexData temp[] = {
						ParticleVertexData(position, color),
						ParticleVertexData(math::Vector2(position.x, position.y + size.y), color),
						ParticleVertexData(math::Vector2(position.x + size.x, position.y + size.y), color),
						ParticleVertexData(math::Vector2(position.x + size.x, position.y), color)
					};

					glBufferSubData(GL_ARRAY_BUFFER, (4 * sizeof(ParticleVertexData))*count, 4 * sizeof(ParticleVertexData), temp);
					count++;
				}
			}

			// Draw Call
			glDrawElements(GL_TRIANGLES, 6 * m_particleCount, GL_UNSIGNED_INT, 0);

			// Unbind
			glBindVertexArray(0);
		}
	}

	void ParticleSystem::disableDeadParticles()
	{
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (m_particlePool[i]->m_aliveTime >= m_particlePool[i]->m_lifeTime) {
				m_particlePool[i]->disable();
			}
		}
	}

	void ParticleSystem::setUpVAO_VBO()
	{
		// Vertex array for the vertex attrib pointer
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		// VBO buffer
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, PARTICLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW); // Initalize with zero data

		// Vertex attribute pointer strucutre
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexData), nullptr); // position
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ParticleVertexData), reinterpret_cast<GLvoid*>(offsetof(ParticleVertexData, color))); // color

		// Index buffer
		int m_indicesOffset = 0;
		uint m_indices[INDICES_COUNT];
		for (int i = 0; i < INDICES_COUNT; i += 6)
		{
			m_indices[i + 0] = m_indicesOffset + 0;
			m_indices[i + 1] = m_indicesOffset + 1;
			m_indices[i + 2] = m_indicesOffset + 2;

			m_indices[i + 3] = m_indicesOffset + 2;
			m_indices[i + 4] = m_indicesOffset + 3;
			m_indices[i + 5] = m_indicesOffset + 0;

			m_indicesOffset += 4;
		}
		m_indexBuffer = new graphics::IndexBuffer(m_indices, sizeof(m_indices));

		m_indexBuffer->unbind();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void ParticleSystem::CleanUp()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);

		for (int i = 0; i < MAX_PARTICLES; i++) {
			delete m_particlePool[i];
		}
	}

} }
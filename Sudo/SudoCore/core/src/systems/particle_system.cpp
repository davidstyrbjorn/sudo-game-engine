#include"particle_system.h"
#include"../../gl_include.h"

#include"../math/mat4.h"

namespace sudo { namespace sudo_system {
	
	ParticleSystem* ParticleSystem::_instance = nullptr;

	ParticleSystem::ParticleSystem() 
	{
		timer = new utility::Timer();
		timer->Start();
	}

	void ParticleSystem::Start()
	{
		glewInit();
		glewExperimental = true;
		
		// Initalize particle array
		for (int i = 0; i < MAX_PARTICLES; i++) {
			m_particlePool[i] = Particle();
		}
		m_particleCount = 0;

		// Set-up the shader
		m_shader = new graphics::Shader("D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\particle_shader_vertex.txt", "D:\\SudoGameEngine\\Sudo\\SudoCore\\core\\src\\shaders\\particle_shader_fragment.txt");
		m_shader->enable();
		m_shader->setUniformMatrix4x4("projection_matrix", math::Matrix4x4::Orthographic(0, 800, 600, 0, -1, 1));
		m_shader->disable();

		// Set up the rendering buffer
		setUpVAO_VBO();
	}

	void ParticleSystem::Update(float deltaTime)
	{
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (m_particlePool[i].active == true) {
				m_particlePool[i].update(deltaTime);
			}
		}
	}

	void ParticleSystem::Begin()
	{
		m_particleCount = 0;
		for (int i = 0; i < MAX_PARTICLES; i++) {
			if (m_particlePool[i].active) {
				m_particleCount++;
			}
		}

		// Reset
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, PARTICLE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);
	}

	void ParticleSystem::Submit(math::Vector2 a_spawnPosition, math::Vector2 a_particleSize, math::Color a_particleColor, uint a_lifeTime, uint a_particleCount)
	{
		if (m_particleCount < MAX_PARTICLES) {
			m_particlePool[m_particleCount].enable(a_spawnPosition, a_particleSize, a_particleColor, a_lifeTime);
			m_particleCount++;
		}
	}

	void ParticleSystem::Flush()
	{
		// Draw all the particles inside m_particlesToRender
		if (m_particleCount != 0) {

			// Remove all dead particles before rendering
			this->disableDeadParticles();
			// Enable the particle shader
			m_shader->enable();
			// Bind
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_indexBuffer->bind();

			// Add all the particles from m_particlesToDraw list to the buffer
			int count = 0;
			for (int i = 0; i < MAX_PARTICLES; i++) {
				if (m_particlePool[i].active) {
					const math::Vector2& position = m_particlePool[i].position;
					const math::Vector2& size = m_particlePool[i].size;
					const math::Color&   color = m_particlePool[i].color;

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
			if (m_particlePool[i].aliveTime >= m_particlePool[i].lifeTime)
				m_particlePool[i].disbale();
		}
	}

	void ParticleSystem::setUpVAO_VBO()
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	}

} }
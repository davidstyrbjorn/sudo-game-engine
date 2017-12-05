#pragma once

#include"sudo_system.h"
#include"../math/vector2.h"
#include"../math/color.h"
#include"../../definitions.h"

#include<array>
#include<vector>

#include"../graphics/buffers/index_buffer.h"
#include"../graphics/shader.h"

#include"../utility/timer.h"
#include"../utility/sudo_random.h"

#include"../graphics/particle.h"

/*
- This class system will basically work as a glorifed renderer
- It will have methods that takes in arguments to spawn particles such as
-> CreateParticles(pos, color, count, ...)
-> ... could be perhaps, life, 
- It will also handles the rendering of these particles
- The actual particle struct will be created seperate from the ParticleClass
- It's rendering methods will be called by the 'engine-loop' 
*/

namespace sudo { namespace sudo_system { 

struct ParticleFlags {
	enum Flags {
		RANDOM_COLOR		= 0x01,
		RANDOM_VELOCITY		= 0x02,
		GRAVITY_PULL		= 0x03,
	};
};

struct ParticleVertexData {
	ParticleVertexData(const math::Vector2& a_pos, const math::Color& a_color) 
	{
		pos = a_pos;
		color = a_color;
	}
	
	math::Vector2 pos;
	math::Color color;
};

#define MAX_PARTICLES 300
#define PARTICLE_SIZE sizeof(ParticleVertexData) * 4
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES

#define INDICES_COUNT 6*MAX_PARTICLES

class ParticleSystem : public SudoSystem {
	private:
		/* Private constructor */
		ParticleSystem();

		/* Static instance of class */
		static ParticleSystem* _instance;

	public:
		static ParticleSystem* Instance() {
			if (_instance == nullptr)
				_instance = new ParticleSystem();
			return _instance;
		}

		/* Virtual Destructor */
		virtual ~ParticleSystem() { }

		/* Gets called on engine initialization */
		void Start();
		/* Gets called on engine update */
		void Update() { }
		void Update(float deltaTime);
		
		/* Enables system */
		void Enable() { m_isActive = true; }
		/* Disable system */
		void Disable() { m_isActive = false; }
		/* Cleans up the necessary thing to prevent memory leaks when quitting */
		void CleanUp();

		// Renderer routines
		void Begin();
		void Submit(ParticleFlags::Flags a_flag, math::Vector2 a_spawnPosition, math::Vector2 a_particleSize, math::Color a_particleColor, uint a_lifeTime);
		void Flush();

	private:
		void disableDeadParticles();

	private:
		/* Particle system data members */
		bool m_isActive;
		uint m_vbo, m_vao;
		std::array<graphics::Particle, MAX_PARTICLES> m_particlePool;
		int m_particleCount;
		graphics::Shader *m_shader;
		graphics::IndexBuffer *m_indexBuffer;
		utility::Timer *timer;

		/* Streamline method for init work */
		void setUpVAO_VBO();
	};

} } 
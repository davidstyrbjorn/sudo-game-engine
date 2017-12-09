#pragma once

#include"sudo_system.h"
#include<array>
#include"../../definitions.h"

#include"../utility/timer.h"

/*
* This class system will basically work as a glorified renderer
* It will have a method that takes in arguments to spawn particles 
* CreateParticles(pos, color, count, ...)
* ... = life etc 
* It will also handles the rendering of these particles
* The actual particle struct will be created seperate from the ParticleClass
* It's rendering methods will be called by the 'engine-loop' 
*/

namespace sudo {
	namespace math {
		class Vector3;
		class Vector2;
		class Color;
	}
	namespace graphics {
		struct Particle;
		class Shader;
		class IndexBuffer;
	}
}

namespace sudo { namespace sudo_system { 

#define MAX_PARTICLES 1000

struct ParticleConfiguration {
	// Values sent in by the user used when spawning particles 
	bool DoFade;
	bool GravitySimulated;
	float GravityScale;

	// The constructor will set all the config values to their default
	ParticleConfiguration() {
		DoFade = false;
		GravitySimulated = false;
		GravityScale = PARTICLE_GRAVITY_Y;
	}
};

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
		// Base constructor   
		void Submit(
			math::Vector3 a_spawnPosition,
			math::Vector2 a_particleSize,
			math::Color a_particleColor,
			uint a_lifeTime,
			math::Vector2 a_velocity,
			ParticleConfiguration a_config
		);
		void Flush();

	private:
		void disableDeadParticles();

	private:
		/* Particle system data members */
		bool m_isActive;
		uint m_vbo, m_vao;
		std::array<graphics::Particle*, MAX_PARTICLES> m_particlePool;
		int m_particleCount;
		graphics::Shader *m_shader;
		graphics::IndexBuffer *m_indexBuffer;
		utility::Timer *timer;

		/* Streamline method for init work */
		void setUpVAO_VBO();
	};

} } 
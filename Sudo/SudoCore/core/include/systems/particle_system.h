#pragma once

#include"sudo_system.h"
#include<array>
#include"../graphics/renderer_base.h"
#include"../definitions.h"
#include"../sudo_behaviour.h"

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

class ParticleSystem : public SudoSystem, public graphics::RendererBase, public SudoBehaviour {
	private:
		// Private constructor 
		ParticleSystem();
		static ParticleSystem* _instance;

	public:
		// Singleton connection
		static ParticleSystem* Instance();
		
		// SudoBehaviour
		void Start() override;
		void Update(float deltaTime) override;
		
		// SudoSystem
		void Enable() override;
		void Disable() override;
		void CleanUp() override;
		bool IsActive() override { return m_isActive; }
		void Toggle() override;

		// Renderer routines
		void Begin() override;
		void Flush() override;
		void End() override { }

		// Submits particle
		void Submit(
			math::Vector3 a_spawnPosition,
			math::Vector2 a_particleSize,
			math::Color a_particleColor,
			uint a_lifeTime,
			math::Vector2 a_velocity,
			ParticleConfiguration a_config
		);

	private:
		// Private methods
		void disableDeadParticles();
		void setUpVAO_VBO();

	private:
		// Data
		bool m_isActive;
		uint m_vbo, m_vao;
		std::array<graphics::Particle*, MAX_PARTICLES> m_particlePool;
		int m_particleCount;
		graphics::Shader *m_shader;
		graphics::IndexBuffer *m_indexBuffer;

	};

} } 
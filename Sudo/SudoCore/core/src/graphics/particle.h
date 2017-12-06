#pragma once

#include"../math/vector2.h"
#include"../math/color.h"

namespace sudo { namespace graphics {

#define GRAVITY 0.001f

	struct Particle {
		// Core members
		math::Vector2 m_position;
		math::Vector2 m_size;
		math::Vector2 m_velocity;
		math::Color m_color;
		float m_lifeTime;
		
		// Hidden members used inside the class
		float m_aliveTime;
		bool m_active;

		// Special members set by the ParticleConfiguration values in ParticleSystem::Submit();
		bool m_gravitySimulated;
		bool m_doAlphaBlend;
		float m_gravityScale;

		// Empty constructor
		Particle() { }

		void init(const math::Vector2 &a_position, const math::Vector2 &a_size, const math::Color &a_color, const math::Vector2& a_velocity, float a_lifeTime)
		{
			m_active = true;

			m_position = a_position;
			m_size = a_size;
			m_color = a_color;
			m_velocity = a_velocity;
			m_lifeTime = a_lifeTime;
			m_aliveTime = 0;
		}

		void disable() 
		{
			m_active = false;
			m_position = math::Vector2(0, 0);
			m_size = math::Vector2(0, 0);
			m_color = math::Color(0, 0, 0, 0);
			m_aliveTime = 0;
			m_lifeTime = 0;

			m_velocity = math::Vector2(0, 0);
		}

		void update(float deltaTime)
		{
			// Life time of the particle
			m_aliveTime += deltaTime;

			// Updating its position
			m_position = math::Vector2(m_position.x + m_velocity.x * deltaTime, m_position.y + m_velocity.y * deltaTime);

			if (m_gravitySimulated) {
				// Adding gravity
				m_velocity = math::Vector2(m_velocity.x, m_velocity.y + m_gravityScale * deltaTime);
			}

			if (m_doAlphaBlend) {
				// Update the alpha value of the particle
				float lifeRatio = m_aliveTime / m_lifeTime;
				m_color.a = 255 * (1 - lifeRatio);
			}
		}
	};

} }
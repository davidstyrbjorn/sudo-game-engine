#pragma once

#include"../math/vector2.h"
#include"../math/color.h"

namespace sudo { namespace graphics {

	struct Particle {
		math::Vector2 m_position;
		math::Vector2 m_size;
		math::Color m_color;
		float m_lifeTime, m_aliveTime;
		bool m_active;

		Particle() { }


		void init(const math::Vector2 &a_position, const math::Vector2 &a_size, const math::Color &a_color, float a_lifeTime)
		{
			m_active = true;

			m_position = a_position;
			m_size = a_size;
			m_color = a_color;
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
		}

		void update(float deltaTime)
		{
			m_aliveTime += deltaTime;
		}
	};

} }
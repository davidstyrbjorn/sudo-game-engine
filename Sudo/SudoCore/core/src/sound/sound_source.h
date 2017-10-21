#pragma once

#include<al.h>
#include<alc.h>

#include"../math/vector3.h"

namespace sudo { namespace sound { 

	class SoundSource {
	private:
		ALuint source;
		math::Vector3 m_position;

	public:
		/* Default constructor */
		SoundSource(ALuint a_buffer);

		/* Property functions */
		const math::Vector3& getPosition() { return m_position; }
		void setPosition(const math::Vector3& a_position);
		void setVolume(const float a_gain);

		/* State modify methods */
		void play();
		void pause();
		void stop();
		void restart();
	};

} } 
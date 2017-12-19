#pragma once

#include<al.h>
#include<alc.h>

namespace sudo {
	namespace math {
		class Vector3;
}
namespace sound { 

	class SoundSource {
	private:
		ALuint source;

	public:
		// Constructor
		SoundSource(ALuint a_buffer);

		// Destructor 
		~SoundSource();

		// Property functions ie. alSource()
		const math::Vector3& getPosition();
		void setPosition(const math::Vector3& a_position);
		void setVolume(const float a_gain);
		void setLooping(unsigned char a_loop);
		void setPitch(const float a_pitch);

		// State modify methods 
		void play(bool a_override = false);
		void pause();
		void stop();
		void restart();
	};

} } 
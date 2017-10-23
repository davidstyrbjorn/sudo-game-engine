#include"sound_system.h"

#include"../debug.h"
#include"../math/vector2.h"
#include"../math/vector3.h"

#include<Windows.h>

namespace sudo { namespace sudo_system {

	SoundSystem* SoundSystem::_instance = nullptr;

	SoundSystem::SoundSystem()
	{
		// Open the soundcard device
		m_device = alcOpenDevice(NULL);

		// Open the context
		m_context = alcCreateContext(m_device, NULL);
		alcMakeContextCurrent(m_context);

		// Error checking
		if (m_context == nullptr || m_device == nullptr) 
		{
			DEBUG::getInstance()->printMessage("Cannot open required sound components for sound system!", LogType::Warning);
			this->CleanUp();
			return;
		}

		alListenerf(AL_GAIN, 1);
		//alListener3f(AL_POSITION, 0, 0, 0);
		this->SetListenerPosition(math::Vector3(0, 0, 0));
	}

	void SoundSystem::Start()
	{

	}

	void SoundSystem::CleanUp()
	{	
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}

	void SoundSystem::SetListenerPosition(const math::Vector3 & a_position)
	{
		alListener3f(AL_POSITION, a_position.x, a_position.y, a_position.z);
	}

	void SoundSystem::SetListenerGain(const float a_gain)
	{
		alListenerf(AL_GAIN, a_gain);
	}
	
} }
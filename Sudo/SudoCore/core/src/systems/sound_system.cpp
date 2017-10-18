#include"sound_system.h"

#include"../debug.h"

namespace sudo { namespace sudo_system {

	SoundSystem* SoundSystem::_instance = nullptr;

	SoundSystem * SoundSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new SoundSystem();
		return _instance;
	}

	void SoundSystem::Start()
	{
		// Open the soundcard device
		m_device = alcOpenDevice(0);

		// Open the context
		m_context = alcCreateContext(m_device, 0);

		// Error checking
		if (m_context == nullptr || m_device == nullptr) {
			DEBUG::getInstance()->printMessage("Failed to load required SoundSystem objects", LogType::Warning);
		}
	}

	void SoundSystem::CleanUp()
	{
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
	}
	
} }
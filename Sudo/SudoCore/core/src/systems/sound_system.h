#pragma once

#include"sudo_system.h"

#include<al.h>
#include<alc.h>

namespace sudo {
	namespace math {
		class Vector3;
		class Vector2;
} }

namespace sudo { namespace sudo_system {

	class SoundSystem : public SudoSystem {
	private:
		SoundSystem() { }
		static SoundSystem *_instance;

	public:
		static SoundSystem *Instance()
		{
			if (_instance == nullptr)
				_instance = new SoundSystem();
			return _instance;
		}
		
		// Must be overiden (spelling)
		#pragma region Base Class Methods
		void Start() override;
		void Update() override { }

		void Enable() override { m_isActive = true; }
		void Disable() override { m_isActive = false; }
		void CleanUp() override;

		void SetListenerPosition(const math::Vector3& a_position);
		void SetListenerGain(const float a_gain);
		#pragma endregion

	private:
		/* Data for the sound system */
		ALCdevice *m_device;
		ALCcontext *m_context;

		unsigned char m_isActive;
	};

} }
#pragma once

#include"sudo_system.h"

#include<al.h>
#include<alc.h>

namespace sudo { namespace sudo_system {

	class SoundSystem : public SudoSystem{
	private:
		SoundSystem();
		static SoundSystem *_instance;

	public:
		static SoundSystem *Instance();
		
		// Must be overiden (spelling)
		#pragma region Base Class Methods
		void Start() override;
		void Update() override { }

		void Enable() override { m_isActive = true; }
		void Disable() override { m_isActive = false; }
		void CleanUp() override;
		#pragma endregion

	private:
		/* Data for the sound system */
		ALCdevice *m_device;
		ALCcontext *m_context;

		unsigned char m_isActive;
	};

} }
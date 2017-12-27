#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include<al.h>
#include<alc.h>

namespace sudo {
	namespace math {
		class Vector3;
		class Vector2;
} }

namespace sudo { namespace sudo_system {

	class SoundSystem : public SudoSystem, public SudoBehaviour {
	private:
		SoundSystem();
		static SoundSystem *_instance;

	public:
		// Singleton connection
		static SoundSystem *Instance();
		
		// SudoBehaviour
		void Start() override;
		void Update(float deltaTime) override { }

		// SudoSystem
		void Enable() override { m_isActive = true; }
		void Disable() override { m_isActive = false; }
		void CleanUp() override;
		bool IsActive() override { return m_isActive; }
		void Toggle() override { m_isActive = !m_isActive; }

		// SoundSystem methods
		void SetListenerPosition(const math::Vector3& a_position);
		void SetListenerGain(const float a_gain);

	private:
		// Data
		ALCdevice *m_device;
		ALCcontext *m_context;
		bool m_isActive;
	};

} }
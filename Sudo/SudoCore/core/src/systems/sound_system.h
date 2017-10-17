#pragma once

#include"sudo_system.h"

#include<al.h>
#include<alc.h>

namespace sudo { namespace sudo_system {

	class SoundSystem : public SudoSystem{
	private:
		static SoundSystem *_instance;

	public:
		static SoundSystem *Instance() {
			if (_instance == nullptr) {
				_instance = new SoundSystem();
			}
			return _instance;
		}
		
		// Must be overiden (spelling)
		#pragma region Base Class Methods
		void Start() override { }
		void Update() override { }

		void Enable() override;
		void Disable() override;
		void CleanUp() override;
		#pragma endregion
	};

} }
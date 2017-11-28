#pragma once

#include"../sudo.h"

namespace sudo {

	/* User class have to inherit from this class and then override Start and Update */

	class SudoClass {
	public:
		sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
		sudo_system::BatchRendererSystem *renderer = sudo_system::BatchRendererSystem::Instance();
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		sudo_system::SettingsSystem *config = sudo_system::SettingsSystem::Instance();
		sudo_system::SoundSystem *sound = sudo_system::SoundSystem::Instance();

	public:
		virtual ~SudoClass() { }

		/* Gets called upon engine init */
		virtual void Start() { }

		/* Gets called once every frame, before renderer flushes and entities gets updated */
		virtual void Update(float deltaTime) { }

		/* Gets called on a fixed time pattern */
		virtual void FixedUpdate() { } 

		/* Gets called when application ends, after the engine is done un-initilazing */
		virtual void OnApplicationQuit() { }

		/* Time between frames, is set by the engine game loop */
		double deltaTime;
	};
}
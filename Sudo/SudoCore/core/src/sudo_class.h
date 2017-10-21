#pragma once

#include"../sudo.h"

namespace sudo {

	/* User class have to inherit from this class and then override Start and Update */

	class SudoClass {
	public:
		sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
		sudo_system::RenderSystem *renderer = sudo_system::RenderSystem::Instance();
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		sudo_system::SettingsSystem *config = sudo_system::SettingsSystem::Instance();
		sudo_system::SoundSystem *sound = sudo_system::SoundSystem::Instance();

	public:
		virtual ~SudoClass() { };

		virtual void Start() { };
		virtual void Update() { };
	};
}
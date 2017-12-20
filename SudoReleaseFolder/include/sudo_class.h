#pragma once

#include"systems\batch_render_system.h"
#include"systems\input_system.h"
#include"systems\world_system.h"
#include"systems\settings_system.h"
#include"systems\sound_system.h"
#include"systems\text_system.h"
#include"systems\particle_system.h"

namespace sudo {

	class SudoClass {
	public:
		// Getting all the systems for the user to exploit
		sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
		sudo_system::BatchRendererSystem *renderer = sudo_system::BatchRendererSystem::Instance();
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		sudo_system::SettingsSystem *config = sudo_system::SettingsSystem::Instance();
		sudo_system::SoundSystem *sound = sudo_system::SoundSystem::Instance();
		sudo_system::TextSystem *textRenderer = sudo_system::TextSystem::Instance();
		sudo_system::ParticleSystem *particleSystem = sudo_system::ParticleSystem::Instance();

	public:
		virtual ~SudoClass() { }

		// Behaviour methods
		virtual void Start() { }
		virtual void Update(float deltaTime) { }
		virtual void LateUpdate(float deltaTime) { }
		virtual void Render() { };
		virtual void OnWindowClose() { }
		virtual void OnApplicationClose() { }
	};

}
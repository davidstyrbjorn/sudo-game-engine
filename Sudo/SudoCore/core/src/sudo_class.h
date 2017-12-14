#pragma once

#include"systems\batch_render_system.h"
#include"systems\input_system.h"
#include"systems\world_system.h"
#include"systems\settings_system.h"
#include"systems\sound_system.h"
#include"systems\text_system.h"
#include"systems\particle_system.h"

namespace sudo {

	/* User class have to inherit from this class and then override Start and Update */
	class SudoClass {
	public:
		sudo_system::InputSystem *input = sudo_system::InputSystem::Instance();
		sudo_system::BatchRendererSystem *renderer = sudo_system::BatchRendererSystem::Instance();
		sudo_system::WorldSystem *world = sudo_system::WorldSystem::Instance();
		sudo_system::SettingsSystem *config = sudo_system::SettingsSystem::Instance();
		sudo_system::SoundSystem *sound = sudo_system::SoundSystem::Instance();
		sudo_system::TextSystem *textRenderer = sudo_system::TextSystem::Instance();
		sudo_system::ParticleSystem *particleSystem = sudo_system::ParticleSystem::Instance();

	public:
		virtual ~SudoClass() { }

		/* Gets called upon engine init */
		virtual void Start() { }

		/* Gets called once every frame, before renderer flushes and entities gets updated */
		virtual void Update(float deltaTime) { }

		/* Gets called after Update, no exceptions */
		virtual void LateUpdate(float deltaTime) { }

		/* Gets called before the renderer's flush gets called */
		virtual void Render() { };

		/* Gets called the instant the OpenGL context window is closed */
		virtual void OnWindowClose() { }

		/* Gets called after the engine is done uninitializing */
		virtual void OnApplicationClose() { }

		/* Time between frames, is set by the engine game loop */
		double deltaTime;
	};
}
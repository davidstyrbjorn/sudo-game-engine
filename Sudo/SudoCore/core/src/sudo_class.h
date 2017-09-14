#pragma once

#include"../sudo.h"

namespace sudo {

	/* User class have to inherit from this class and then override Start and Update */

	class SudoClass {
	public:
		system::InputSystem *input = system::InputSystem::Instance();
		system::RenderSystem *renderer = system::RenderSystem::Instance();
		system::WorldSystem *world = system::WorldSystem::Instance();
		system::SettingsSystem *config = system::SettingsSystem::Instance();

	public:
		virtual ~SudoClass() { };

		virtual void Start() { };
		virtual void Update() { };
	};

}
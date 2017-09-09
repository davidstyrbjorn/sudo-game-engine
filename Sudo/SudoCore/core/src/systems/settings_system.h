#pragma once

#include"sudo_system.h"

#include"../math/vector2.h"

namespace sudo { namespace system {

	class SettingsSystem : SudoSystem {
	private:
		// Private construcotr since this is a singleton class
		SettingsSystem() { }

		// Private instance
		static SettingsSystem *_instance;

	public:
		/* Method to get pointer to _instace */
		static SettingsSystem *Instance();

		#pragma region Base Class Methods
		void Start() override { }
		void Update() override { } 

		void Enable() override { }
		void Disable() override { } 
		void CleanUp() override { }
		#pragma endregion
		#pragma region Getters
		/* Returns the currently set window size */
		const math::Vector2& GetWindowSize();

		/* Returns the currently set FPS */
		unsigned int GetFPS() const;
		#pragma endregion
		#pragma region Setters
		/* Sets m_windowSize to a new size */
		void SetWindowSize(const math::Vector2& a_newWindowSize);

		/* Sets m_fps to a new value */
		void SetFPS(const unsigned int a_newFPS);
		#pragma endregion

	private:
		/* Settings data */
		math::Vector2 m_windowSize;
		unsigned int m_fps;
	};
} } 
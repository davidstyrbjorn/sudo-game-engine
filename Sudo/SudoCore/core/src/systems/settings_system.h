#pragma once

#include"sudo_system.h"

#include"../math/vector2.h"
#include"../math/vector4.h"

namespace sudo {
	namespace utility {
		class SudoString;
} }

namespace sudo { namespace sudo_system {

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

		/* Returns the currently set MS per frame */
		double GetMS() const;

		/* Returns the current window background color */
		const math::Vector4& GetBackgroundColor();
		#pragma endregion
		#pragma region Setters
		/* Sets m_windowSize to a new size */
		void SetWindowSize(math::Vector2& a_newWindowSize);

		/* Sets window background color */
		void SetBackgroundColor(const math::Vector4& a_newBackgroundColor);
		void SetBackgroundColor(const double a_newBackgroundColor);

		void SetWindowCaption(const char* a_newCaption);

		/* Sets m_fps to a new value */
		void SetFPS(const unsigned int a_newFPS);
		#pragma endregion

	private:
		/* Settings data */
		math::Vector2 m_windowSize;
		math::Vector4 m_backgroundColor;
		unsigned int m_fps;
		double m_msPerFrame;

		/* Private methods not to be called by anyone else */
		void NewFpsValue() {
			m_msPerFrame = 1000 / m_fps;
		}
	};
} } 
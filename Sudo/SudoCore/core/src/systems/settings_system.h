#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include"../math/vector2.h"
#include"../math/vector4.h"
#include"../math/color.h"

namespace sudo { namespace sudo_system {

	class SettingsSystem : public SudoSystem, public SudoBehaviour {
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
		void Update(float deltaTime) override { } 

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
		const math::Color& GetBackgroundColor();

		/* Returns m_autoRender to determine behaviour in renderer */
		const bool DoAutoRender();
		#pragma endregion
		#pragma region Setters
		/* Sets m_windowSize to a new size */
		void SetWindowSize(math::Vector2& a_newWindowSize);

		/* Sets window background color */
		void SetBackgroundColor(const math::Color& a_newBackgroundColor);
		void SetBackgroundColor(const double a_newBackgroundColor);

		void SetWindowCaption(const char* a_newCaption);
		void SetAutoRender(bool a_value);

		/* Sets m_fps to a new value */
		void SetFPS(const unsigned int a_newFPS);
		#pragma endregion

		void* instancePtr; // Ugly pointer to current engine instance

	private:
		/* Settings data */
		math::Vector2 m_windowSize;
		math::Color m_backgroundColor;
		unsigned int m_fps;
		double m_msPerFrame;
		bool m_autoRender; // If enabled auto render all the entities with renderable2D components

		/* Private methods not to be called by anyone else */
		void NewFpsValue() {
			if (m_fps > 0)
				m_msPerFrame = 1000 / m_fps;
			else
				m_msPerFrame = 0;
		}
	};
} } 
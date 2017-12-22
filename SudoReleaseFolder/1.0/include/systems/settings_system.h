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
		/////////////////
		// Public methods
		/////////////////

		// Singleton connection 
		static SettingsSystem *Instance();

		// SudoBehaviour 

		// Settings base class
		void Enable() override { }
		void Disable() override { } 
		void CleanUp() override { }

		// Getters
		const math::Vector2& GetWindowSize();
		unsigned int GetFPS() const;
		double GetMS() const;
		const math::Color& GetBackgroundColor();
		const bool DoAutoRender();

		// Setters
		void SetWindowSize(math::Vector2& a_newWindowSize);
		void SetBackgroundColor(const math::Color& a_newBackgroundColor);
		void SetBackgroundColor(const double a_newBackgroundColor);
		void SetWindowCaption(const char* a_newCaption);
		void SetAutoRender(bool a_value);
		void SetFPS(const unsigned int a_newFPS);

		// Game class 
		template<typename GameClass>
		GameClass *GetGameClass() {
			return static_cast<GameClass*>(instancePtr);
		}
		void* instancePtr; 

	private:
		/////////////////
		// Private methods
		/////////////////

		void NewFpsValue();

	private:
		/* Settings data */
		math::Vector2 m_windowSize;
		math::Color m_backgroundColor;
		unsigned int m_fps;
		double m_msPerFrame;
		bool m_autoRender; // If enabled auto render all the entities with renderable2D components

	};
} } 
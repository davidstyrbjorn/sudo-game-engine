#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include"../math/vector2.h"
#include"../math/vector4.h"
#include"../math/color.h"

namespace sudo { namespace sudo_system {

	enum SudoRenderMode {
		NORMAL,
		WIRE_FRAME_MODE
	};

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
		bool IsActive() override { return true; }
		void Toggle() override { }

		// Getters
		const math::Vector2& GetWindowSize();
		unsigned int GetFPS() const;
		double GetMS() const;
		const math::Color& GetBackgroundColor();
		const bool DoAutoRender();
		unsigned int GetCurrentFPS() const;
		double GetCurrentMS() const;
		SudoRenderMode GetRenderMode() const;

		// Setters
		void SetWindowSize(math::Vector2& a_newWindowSize);
		void SetBackgroundColor(const math::Color& a_newBackgroundColor);
		void SetBackgroundColor(const double a_newBackgroundColor);
		void SetWindowCaption(const char* a_newCaption);
		void SetAutoRender(bool a_value);
		void SetFPS(const unsigned int a_newFPS);
		void SetCurrentFPS(const unsigned int a_currentNewFps);
		void SetCurrentMS(const double a_newMS);
		void SetRenderMode(SudoRenderMode a_mode);

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
		// Varying data 
		unsigned int m_currentFps;
		double m_currentMS;
		SudoRenderMode m_renderMode;

		// Persistent Data
		math::Vector2 m_windowSize;
		math::Color m_backgroundColor;
		unsigned int m_fps;
		double m_msPerFrame;
		bool m_autoRender; // If enabled auto render all the entities with renderable2D components

	};
} } 
#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include"../definitions.h"

struct GLFWwindow;

namespace sudo {
	namespace debug {
		class SudoImGui;
} }

namespace sudo { namespace sudo_system {

	class WindowSystem : public SudoSystem, public SudoBehaviour {
	private:
		// Singleton
		static WindowSystem *_instance;
		WindowSystem() { }

	public:
		// Singleton connection
		static WindowSystem* Instance();

		// Window Method
		void Init(uint a_width, uint a_height, char* a_caption);
		void Clear();
		void Display();
		bool IsOpen();
		void WindowShake(float a_length, int a_intensity);

		// Methods from SudoBehaviour super class 
		void Start() override { }
		void Update(float deltaTime) override;

		// Methods from SudoSystem super class 
		void Enable() override;
		void Disable() override;
		void CleanUp() override;
		bool IsActive() override { return m_isActive; }
		void Toggle() override;

	private:
		// Window Data
		GLFWwindow *m_window;
		bool m_isActive;
		debug::SudoImGui *m_debugObject;

		// *window shake values
		float m_windowShakeLength;
		int m_windowShakeStrength;
		int m_windowOrgX, m_windowOrgY;
		bool m_doWindowShake;

		// GLFW Callback functions 
		friend static void window_size_callback(GLFWwindow* window, int width, int height);
		friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};

} } 

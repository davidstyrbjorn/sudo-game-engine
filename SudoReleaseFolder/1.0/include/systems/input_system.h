#pragma once

#include"../gl_include.h"
#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include<map>

// Forward decleration
namespace sudo {
	namespace math {
		struct Vector2;
	}
}

namespace sudo { namespace sudo_system {

	class InputSystem : public SudoSystem, public SudoBehaviour {
	private:
		// Private constructor
		InputSystem() { }
		static InputSystem *_instance;

		// Input class data
		std::map<const char*, int> keyCodeToLiteral;

		float m_windowShakeLength;
		int m_windowShakeStrength;
		int m_windowOrgX, m_windowOrgY;
		bool m_doWindowShake;

		int m_keys[1024];
		int m_mouseKeys[24];
		math::Vector2 *m_mousePos;

	public:
		// Singleton connection
		static InputSystem *Instance();

		// Methods from the SudoSystem base class 
		void Enable() override;
		void Disable() override;
		void CleanUp() override;

		// SudoBehaviour 
		void Update(float deltaTime) override;

		// End-user input methods
		bool GetKeyDown(const char* a_key);
		bool GetKey(const char* a_key);
		bool IsMouseButtonPressed(int a_mouse_button);

		// Shakes GLFW window 
		void WindowShake(float a_length, int a_intensity);

		// Populates keyCodeToiteral map
		void populateKeyList();

		/* GLFW Callbacks */
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	};

}
}
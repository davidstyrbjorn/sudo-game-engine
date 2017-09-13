#pragma once

#include"../../gl_include.h"
#include"sudo_system.h"

#include<map>

// Forward decleration
namespace sudo {
	namespace math {
		class Vector2;
	}
}

namespace sudo { namespace system {

	class InputSystem : public SudoSystem {
	private:
		/* Private constructor since this is a singleton class */
		InputSystem() { }

		/* The Private instance */
		static InputSystem *_instance;

		std::map<const char*, int> keyCodeToLiteral;

	public:
		int m_keys[1024];

		int m_mouseKeys[24];
		math::Vector2 *m_mousePos;

	public:
		/* Method to get pointer to _instance */
		static InputSystem *Instance();

		/* Methods from the SudoSystem base class */
		void Enable() override;
		void Disable() override;
		void CleanUp() override;

		/* end-user methods */
		/* Returns true if a_keycode is down */
		bool GetKeyDown(const char* a_key);
		bool GetKey(const char* a_key);

		/* end-user static function */
		/* Returns true if a_mouse_button is down */
		bool IsMouseButtonPressed(int a_mouse_button);

		/* GLFW Callbacks */
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	public:
		void populateKeyList();
	};

}
}
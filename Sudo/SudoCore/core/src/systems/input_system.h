#pragma once

#include<map>

#include"GLFW\glfw3.h"
#include"../../gl_include.h"
#include"sudo_system.h"


// Forward decleration
namespace sudo {
	namespace math {
		class Vector2;
	}
}

struct Key {
	Key(int a_action, const char* a_keyName) {
		this->m_action = a_action;
		this->m_keyName = a_keyName;
	}

	int m_action;
	const char* m_keyName;
};

namespace sudo { namespace system {

	class InputSystem : public SudoSystem {
	private:
		/* Private constructor since this is a singleton class */
		InputSystem() { }

		/* The Private instance */
		static InputSystem *_instance;

	public:
		int m_keys[1024];
		int m_mouseKeys[24];
		Key keyList[1024];
		math::Vector2 *m_mousePos;

	public:
		/* Method to get pointer to _instance */
		static InputSystem *Instance();

		/* Methods from the SudoSystem base class */
		void Enable() override;
		void Disable() override;
		void CleanUp() override;

		/* end-user static function */
		/* Returns true if a_keycode is down */
		bool IsKeyPressed(int a_keycode);

		/* end-user static function */
		/* Returns true if a_mouse_button is down */
		bool IsMouseButtonPressed(int a_mouse_button);

		/* GLFW Callbacks */
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	private:
		void populateKeyList();
	};

}
}
#pragma once

#include"sudo_system.h"
#include"../sudo_behaviour.h"

#include<map>

// Forward decleration
namespace sudo {
	namespace math {
		struct Vector2;
	}
}

// GLFW forward declaration
struct GLFWwindow;

namespace sudo { namespace sudo_system {

	class InputSystem : public SudoSystem, public SudoBehaviour {
	private:
		// Private constructor
		InputSystem() { }
		static InputSystem *_instance;

		// Input class data
		bool m_isActive = false;

		std::map<const char*, int> keyCodeToLiteral;

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
		bool IsActive() override { return m_isActive; }
		void Toggle() override;

		// SudoBehaviour 
		void Update(float deltaTime) override;

		// End-user input methods
		bool GetKeyDown(const char* a_key);
		bool GetKey(const char* a_key);
		bool IsMouseButtonPressed(int a_mouse_button);

		// Getters
		const math::Vector2 &GetMousePosition();

		// Populates keyCodeToiteral map
		void populateKeyList();

		/* GLFW Callbacks */
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void character_callback(GLFWwindow* window, unsigned int codepoint);
	};

}
}
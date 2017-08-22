#include "input_system.h"
#include"../../sudo.h"

namespace sudo { namespace system {

	math::Vector2 InputSystem::m_mousePos = math::Vector2(0, 0);
	int InputSystem::m_keys[1024] = { GLFW_RELEASE };
	int InputSystem::m_mouseKeys[24] = { GLFW_RELEASE };

	void InputSystem::EnableInputSystemSystem()
	{
		/* Set the GLFW callbacks */
		glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
		glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);
	}

	void InputSystem::DisableInputSystemSystem()
	{
		/* Set the GLFW callbacks */
		glfwSetCursorPosCallback(glfwGetCurrentContext(), nullptr);
		glfwSetKeyCallback(glfwGetCurrentContext(), nullptr);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), nullptr);
	}

	bool InputSystem::IsKeyPressed(int a_keycode)
	{
		if (m_keys[a_keycode] == GLFW_PRESS || m_keys[a_keycode] == GLFW_REPEAT)
			return true;
		return false;
	}
	
	bool InputSystem::IsMouseButtonPressed(int a_mouse_button)
	{
		if (m_mouseKeys[a_mouse_button] == GLFW_PRESS || m_mouseKeys[a_mouse_button] == GLFW_REPEAT)
			return true;
		return false;
	}

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		InputSystem::m_keys[key] = action;
	}

	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		InputSystem::m_mousePos = math::Vector2((float)xpos, (float)ypos);
	}

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		InputSystem::m_mouseKeys[button] = action;
	}

}
}

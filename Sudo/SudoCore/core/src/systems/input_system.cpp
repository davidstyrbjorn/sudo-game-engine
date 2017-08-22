#include "input_system.h"
#include"../math/vector2.h"

namespace sudo { namespace system {

	InputSystem* InputSystem::_instance = nullptr;

	InputSystem * InputSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new InputSystem();
		return _instance;
	}

	void InputSystem::Enable()
	{
		/* Set the GLFW callbacks */
		glfwSetCursorPosCallback(glfwGetCurrentContext(), cursor_position_callback);
		glfwSetKeyCallback(glfwGetCurrentContext(), key_callback);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), mouse_button_callback);

		m_mousePos = new math::Vector2(0, 0);
	}

	void InputSystem::Disable() 
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
		InputSystem* tmp = InputSystem::Instance();
		tmp->m_keys[key] = action;
	}

	void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
	{
		InputSystem* tmp = InputSystem::Instance();
		tmp->m_mousePos->setX((float)xpos);
		tmp->m_mousePos->setY((float)ypos);
	}

	void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
	{
		InputSystem* tmp = InputSystem::Instance();
		tmp->m_mouseKeys[button] = action;
	}

}
}

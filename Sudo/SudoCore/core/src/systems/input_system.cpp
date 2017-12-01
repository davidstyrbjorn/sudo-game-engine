#include "input_system.h"
#include"../../sudo.h"
#include<time.h>

namespace sudo { namespace sudo_system {

	InputSystem* InputSystem::_instance = nullptr;

	InputSystem * InputSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new InputSystem();
		return _instance;
	}

	void InputSystem::Update()
	{
		/* Window Shake Code */
		if (m_doWindowShake) {
			// Get the window's new position values for this frame
			int _x = utility::SudoRandomNumber::GetRandomInteger<int>(-m_windowShakeStrength, m_windowShakeStrength);
			int _y = utility::SudoRandomNumber::GetRandomInteger<int>(-m_windowShakeStrength, m_windowShakeStrength);

			// Set the window's position accordingly
			glfwSetWindowPos(glfwGetCurrentContext(), m_windowOrgX + _x, m_windowOrgY + _y);

			// Decrease the length of the window shake (in frames) 
			m_windowShakeLength--;
			if (m_windowShakeLength <= 0) {
				m_doWindowShake = false;
				glfwSetWindowPos(glfwGetCurrentContext(), m_windowOrgX, m_windowOrgY);
			}
		}
	}

	void InputSystem::Enable()
	{
		srand(time(NULL));
		populateKeyList();

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

	void InputSystem::CleanUp() 
	{
		// Delete all the allocated memory
		delete m_mousePos;
	}

	bool InputSystem::GetKeyDown(const char* a_key)
	{
		if (m_keys[keyCodeToLiteral[a_key]] == GLFW_PRESS)
			return true;
		return false;
	}

	bool InputSystem::GetKey(const char* a_key) 
	{
		if (m_keys[keyCodeToLiteral[a_key]] == GLFW_PRESS || m_keys[keyCodeToLiteral[a_key]] == GLFW_REPEAT)
			return true;
		return false;
	}
	
	bool InputSystem::IsMouseButtonPressed(int a_mouse_button)
	{
		if (m_mouseKeys[a_mouse_button] == GLFW_PRESS || m_mouseKeys[a_mouse_button] == GLFW_REPEAT)
			return true;
		return false;
	}

	void InputSystem::WindowShake(float a_length, int a_intensity)
	{
		m_doWindowShake = true;
		m_windowShakeLength = a_length;
		m_windowShakeStrength = a_intensity;
		glfwGetWindowPos(glfwGetCurrentContext(), &m_windowOrgX, &m_windowOrgY);
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

	void InputSystem::populateKeyList()
	{
		keyCodeToLiteral["space"] = 32;
		keyCodeToLiteral[" ' "] = 39;
		keyCodeToLiteral[","] = 44;
		keyCodeToLiteral["-"] = 45;
		keyCodeToLiteral["."] = 46;
		keyCodeToLiteral["/"] = 47;
		keyCodeToLiteral[";"] = 59;
		keyCodeToLiteral["="] = 61;
		keyCodeToLiteral["0"] = 48;
		keyCodeToLiteral["1"] = 49;
		keyCodeToLiteral["2"] = 50;
		keyCodeToLiteral["3"] = 51;
		keyCodeToLiteral["4"] = 52;
		keyCodeToLiteral["5"] = 53;
		keyCodeToLiteral["6"] = 54;
		keyCodeToLiteral["7"] = 55;
		keyCodeToLiteral["8"] = 56;
		keyCodeToLiteral["9"] = 57;

		keyCodeToLiteral["a"] = 65;
		keyCodeToLiteral["b"] = 66;
		keyCodeToLiteral["c"] = 67;
		keyCodeToLiteral["d"] = 68;
		keyCodeToLiteral["e"] = 69;
		keyCodeToLiteral["f"] = 70;
		keyCodeToLiteral["g"] = 71;
		keyCodeToLiteral["h"] = 72;
		keyCodeToLiteral["i"] = 73;
		keyCodeToLiteral["j"] = 74;
		keyCodeToLiteral["k"] = 75;
		keyCodeToLiteral["l"] = 76;
		keyCodeToLiteral["m"] = 77;
		keyCodeToLiteral["n"] = 78;
		keyCodeToLiteral["o"] = 79;
		keyCodeToLiteral["p"] = 80;
		keyCodeToLiteral["q"] = 81;
		keyCodeToLiteral["r"] = 82;
		keyCodeToLiteral["s"] = 83;
		keyCodeToLiteral["t"] = 84;
		keyCodeToLiteral["u"] = 85;
		keyCodeToLiteral["v"] = 86;
		keyCodeToLiteral["w"] = 87;
		keyCodeToLiteral["x"] = 88;
		keyCodeToLiteral["y"] = 89;
		keyCodeToLiteral["z"] = 90;

		keyCodeToLiteral["["] = 91;
		keyCodeToLiteral["\\"] = 92;
		keyCodeToLiteral["]"] = 93;

		//#define GLFW_KEY_GRAVE_ACCENT       96  /* ` */
		//#define GLFW_KEY_WORLD_1            161 /* non-US #1 */
		//#define GLFW_KEY_WORLD_2            162 /* non-US #2 */

		// Utility Keys
		keyCodeToLiteral["escape"] = 256;
		keyCodeToLiteral["enter"] = 257;
		keyCodeToLiteral["tab"] = 258;
		keyCodeToLiteral["backspace"] = 259;
		keyCodeToLiteral["insert"] = 260;
		keyCodeToLiteral["delete"] = 261;
		keyCodeToLiteral["right"] = 262;
		keyCodeToLiteral["left"] = 263;
		keyCodeToLiteral["down"] = 264;
		keyCodeToLiteral["up"] = 265;
		keyCodeToLiteral["page_up"] = 266;
		keyCodeToLiteral["page_down"] = 267;
		keyCodeToLiteral["home"] = 268;
		keyCodeToLiteral["end"] = 269;
		keyCodeToLiteral["caps_lock"] = 280;
		keyCodeToLiteral["scroll_lock"] = 281;
		keyCodeToLiteral["num_lock"] = 282;
		keyCodeToLiteral["print_screen"] = 283;
		keyCodeToLiteral["pause"] = 284;

		// f keys
		keyCodeToLiteral["f1"] = 290;
		keyCodeToLiteral["f2"] = 291;
		keyCodeToLiteral["f3"] = 292;
		keyCodeToLiteral["f4"] = 293;
		keyCodeToLiteral["f5"] = 294;
		keyCodeToLiteral["f6"] = 295;
		keyCodeToLiteral["f7"] = 296;
		keyCodeToLiteral["f8"] = 297;
		keyCodeToLiteral["f9"] = 298;
		keyCodeToLiteral["f10"] = 299;
		keyCodeToLiteral["f11"] = 300;
		keyCodeToLiteral["f12"] = 301;
		keyCodeToLiteral["f13"] = 302;
		keyCodeToLiteral["f14"] = 303;
		keyCodeToLiteral["f15"] = 304;
		keyCodeToLiteral["f16"] = 305;
		keyCodeToLiteral["f17"] = 306;
		keyCodeToLiteral["f18"] = 307;
		keyCodeToLiteral["f19"] = 308;
		keyCodeToLiteral["f20"] = 309;
		keyCodeToLiteral["f21"] = 310;
		keyCodeToLiteral["f22"] = 311;
		keyCodeToLiteral["f23"] = 312;
		keyCodeToLiteral["f24"] = 313;
		keyCodeToLiteral["f25"] = 314;
	}
}
}
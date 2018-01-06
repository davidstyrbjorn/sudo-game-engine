#include"../include/systems/window_system.h"

#include"../include/gl_include.h"

#include"../include/systems/settings_system.h"
#include"../include/debug.h"
#include"../include/utility/sudo_random.h"

#include"../include/ImGui/imgui.h" // ImGuiLibrary
#include"../include/ImGui/imgui_glfw.h" // ImGui library
#include"../include/ImGui/sudo_imgui_context.h" // Sudo Class

namespace sudo { namespace sudo_system { 

	WindowSystem* WindowSystem::_instance = nullptr;
	WindowSystem* WindowSystem::Instance()
	{
		if (_instance == nullptr)
			_instance = new WindowSystem();

		return _instance;
	}

	void WindowSystem::Init(uint a_width, uint a_height, char * a_caption)
	{
		// Create the window and setup GLFW
		if (!glfwInit()) {
			DEBUG::getInstance()->printMessage("Failed to create GLFW window!", LogType::Fatal);
		}
		m_window = glfwCreateWindow(a_width, a_height, a_caption, nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);

		// Dear ImGui init
		ImGui_ImplGlfwGL3_Init(m_window, false);
		m_debugObject = new debug::SudoImGui();

		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		glViewport(0, 0, w, h);

		// GLFW callbacks
		glfwSetWindowSizeCallback(m_window, window_size_callback);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	}

	void WindowSystem::Clear()
	{
		// Clear screen and poll events
		SettingsSystem *s = SettingsSystem::Instance();
		glClearColor(s->GetBackgroundColor().r / 255, s->GetBackgroundColor().g / 255, s->GetBackgroundColor().b / 255, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		// Updat debug layer
		ImGui_ImplGlfwGL3_NewFrame();
		//ImGui::ShowTestWindow();
		m_debugObject->ShowMetricsWindow();
		m_debugObject->ShowEntityInspector();
		m_debugObject->ShowSystemsWindow();
		m_debugObject->ShowSystemWidgets();
		m_debugObject->ShowEntitiesWindow();
		m_debugObject->ShowAddEntityWidget();
	}

	void WindowSystem::WindowShake(float a_length, int a_intensity)
	{
		m_doWindowShake = true;
		m_windowShakeLength = a_length;
		m_windowShakeStrength = a_intensity;
		glfwGetWindowPos(glfwGetCurrentContext(), &m_windowOrgX, &m_windowOrgY);
	}

	void WindowSystem::Update(float deltaTime)
	{
		if (m_doWindowShake && m_isActive) {
			// Get the window's new position values for this frame
			int _x = utility::SudoRandomNumber::GetRandomInteger(-m_windowShakeStrength, m_windowShakeStrength);
			int _y = utility::SudoRandomNumber::GetRandomInteger(-m_windowShakeStrength, m_windowShakeStrength);

			// Set the window's position accordingly
			glfwSetWindowPos(glfwGetCurrentContext(), m_windowOrgX + _x, m_windowOrgY + _y);

			// Decrease the length of the window shake 
			m_windowShakeLength -= deltaTime;
			if (m_windowShakeLength <= 0) {
				m_doWindowShake = false;
				glfwSetWindowPos(glfwGetCurrentContext(), m_windowOrgX, m_windowOrgY);
			}
		}
	}

	void WindowSystem::Display()
	{
		ImGui::Render();

		glfwSwapBuffers(m_window);
	}

	bool WindowSystem::IsOpen()
	{
		return !glfwWindowShouldClose(m_window);
	}


	void WindowSystem::Enable()
	{
		m_isActive = true;
	}

	void WindowSystem::Disable()
	{
		m_isActive = false;
	}

	void WindowSystem::Toggle()
	{
		m_isActive = !m_isActive;
	}

	void WindowSystem::CleanUp()
	{
		glfwDestroyWindow(m_window);
	}


	/* GLFW Callback Functions */
	void window_size_callback(GLFWwindow * window, int width, int height)
	{

	}

	void framebuffer_size_callback(GLFWwindow * window, int width, int height)
	{
		//glfwGetFramebufferSize(window, (int*)&temp->m_width, (int*)&temp->m_height);
		glViewport(0, 0, width, height);
	}

}} 
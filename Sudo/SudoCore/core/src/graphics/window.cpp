#include "window.h"

#include"../../sudo.h"

/* Window.cpp */
sudo::graphics::Window::Window(uint a_width, uint a_height, char *a_caption)
{
	m_width = a_width;
	m_height = a_height;

	if (glfwInit() == 0) {
		// Log init error here
		return;
	}

	m_window = glfwCreateWindow(m_width, m_height, a_caption, NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	glViewport(0, 0, width, height);

	/* Set Callbacks */
	glfwSetWindowSizeCallback(m_window, window_size_callback);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	/* Initalize Settings System */
	settings = sudo_system::SettingsSystem::Instance();
}

sudo::graphics::Window::~Window()
{

}

void sudo::graphics::Window::clear() 
{
	glfwPollEvents();

	glClearColor(settings->GetBackgroundColor().x, settings->GetBackgroundColor().y, settings->GetBackgroundColor().z, settings->GetBackgroundColor().w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void sudo::graphics::Window::display() 
{
	if (glfwGetCurrentContext() != nullptr)
	{
		glfwSwapBuffers(m_window);
	}
}

bool sudo::graphics::Window::is_open() 
{
	return !glfwWindowShouldClose(m_window);
}

void sudo::graphics::Window::close()
{
	glfwDestroyWindow(m_window);
}

void sudo::graphics::Window::setWindowPos(const math::Vector2 & a_pos)
{
	std::cout << "Change Window Position" << std::endl;
	glfwSetWindowPos(this->m_window, a_pos.x, a_pos.y);
}

/* GLFW Callback Functions */
void sudo::graphics::window_size_callback(GLFWwindow * window, int width, int height)
{

}

void sudo::graphics::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	sudo::graphics::Window *temp = (sudo::graphics::Window*)glfwGetWindowUserPointer(window);
	glfwGetFramebufferSize(window, (int*)&temp->m_width, (int*)&temp->m_height);

	glViewport(0, 0, width, height);
}
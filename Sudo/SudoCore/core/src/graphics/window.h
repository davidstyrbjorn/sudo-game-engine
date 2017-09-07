#pragma once

#include"../../gl_include.h"
#include"graphics_framework.h"   

#include"../math/vector3.h"

namespace sudo { namespace graphics {

	typedef unsigned int uint;

	class Window : GraphicsFramework {
	public:
		/* Window Public Functions */
		Window(uint a_width, uint a_height, char *a_caption);
		~Window();

		void clear() override;
		void display() override;

		bool is_open() override;
		void close() override;

		void SetBackgroundColor(const math::Vector3 &a_newColor);

	private:
		/* Window Private Data */
		// Window data
		GLFWwindow *m_window;
		uint m_width, m_height;
		math::Vector3 m_backgroundColor;

		/* GLFW Callback functions */
		friend static void window_size_callback(GLFWwindow* window, int width, int height);
		friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};

} }
#pragma once

#include"../../gl_include.h"
#include"graphics_framework.h"   

#include"../math/vector3.h"
#include"../math/vector2.h"

namespace sudo {
	namespace system {
		class SettingsSystem;
	}
}

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

		void setWindowPos(const math::Vector2& a_pos);

	private:
		/* Window Private Data */
		// Window data
		GLFWwindow *m_window;
		uint m_width, m_height;
		system::SettingsSystem *settings;

		/* GLFW Callback functions */
		friend static void window_size_callback(GLFWwindow* window, int width, int height);
		friend static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};

} }
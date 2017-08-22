#pragma once

#include"GLFW\glfw3.h"


	class Time {
	public:
		/* Returns elapsed time since glfw was initalized */
		static double GetElapsedTime() {
			return glfwGetTime();
		}

		/* Resets the glfw timer back to zero */
		static void ResetTime() {
			glfwSetTime(0);
		}
	};
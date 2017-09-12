#pragma once

/*
* FPS <->  MS
* 120  -  0.12
* 60   -  0.06
* 30   -  0.03
* 24   -  0.024
*/
#include"GLFW\glfw3.h"

namespace sudo { namespace utility { 

	class Time {
	public:
		static double GetElapsedTime() {
			return glfwGetTime();
		}

		static void ResetTime() {
			glfwSetTime(0);
		}
	};
}}
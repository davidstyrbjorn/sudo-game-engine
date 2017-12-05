#pragma once

#include<random>
#include<time.h>

namespace sudo { namespace utility { 

	class SudoRandomNumber {
	private:
		static std::random_device m_randomDevice;

	public:
		static int GetRandomInteger(const int a_min, const int a_max) {
			std::mt19937 gen(m_randomDevice());

			std::uniform_int_distribution<int> _distribution(a_min, a_max);
			int _returnValue = _distribution(gen);

			return _returnValue;
		}

		static float GetRandomFloatingPoint(float a_min, float a_max) {
			// Seed the number
			srand(time(NULL));

			// Return the number
			return a_min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (a_max - a_min)));
		}
	};
} } 
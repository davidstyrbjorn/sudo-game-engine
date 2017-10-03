#pragma once

#include<random>

namespace sudo { namespace utility { 

	class SudoRandomNumber {
	private:
		static std::random_device m_randomDevice;

	public:
		template<class T>
		static T GetRandomNumber(T a_min, T a_max) {
			std::mt19937 gen(m_randomDevice());

			std::uniform_int_distribution<T> _distribution(a_min, a_max);
			T _returnValue = _distribution(gen);

			return _returnValue;
		}
	};
} } 
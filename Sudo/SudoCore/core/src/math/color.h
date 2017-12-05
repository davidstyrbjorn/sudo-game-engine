#pragma once

#include<iostream>

namespace sudo {
	namespace math {

		struct Color {
			// Values between 0 - 255
			float r, g, b, a;

			/* Default Constructor */
			Color() : r(0), g(0), b(0), a(255) { }

			/* Takes in values between 0-255 */
			Color(float a_red, float a_green, float a_blue, float a_alpha = 255) : r(a_red), g(a_green), b(a_blue), a(a_alpha) { }

			/* Operator Overloading Methods */
			/* Arithmetic Operators */
			Color operator+(const Color rhs);
			Color operator-(const Color rhs);
			Color operator/(const float rhs);
			Color operator=(const Color &rhs);
			Color operator*(const float scalar);
			Color& operator+=(const Color &rhs);
			Color& operator-=(const Color &rhs);
			Color& operator*=(const float scalar);

			/* Basic colors static methods */
			__forceinline static Color Red() { return Color(255, 0, 0, 255); }
			__forceinline static Color Green() { return Color(0, 255, 0, 255); }
			__forceinline static Color Blue() { return Color(0, 0, 255, 255); }

			friend std::ostream& operator<<(std::ostream &os, const Color &other);
		};

		inline bool operator==(const Color& lhs, const Color& rhs) { return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a); }
		inline bool operator!=(const Color& lhs, const Color& rhs) { return !operator==(lhs, rhs); }

	}
}
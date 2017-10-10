#pragma once

#include<iostream>

namespace sudo { namespace math {

	struct Vector2 {
		float x, y;

		/* Default Constructor */
		Vector2() : x(0), y(0) { }

		/* Constructor (float) */
		Vector2(float a_x, float a_y) : x(a_x), y(a_y) { }

		/* Data Methods */
		void setX(float a_x);
		void setY(float a_y);

		inline static float GetMagnitude(const Vector2& vec) {
			// Return the magnitude of other
			return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
		}

		/* Operator Overloading Methods */
		Vector2 operator+(const Vector2 rhs);
		Vector2 operator-(const Vector2 rhs);
		Vector2 operator=(const Vector2& rhs);
		Vector2 operator*(const float scalar);

		unsigned char operator>(const Vector2 &rhs);
		unsigned char operator<(const Vector2 &rhs);

		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);

		friend std::ostream& operator<<(std::ostream &os, const Vector2 &other);

		/* Static Stuff */
		
	};

	// I have to do this here for some reason, don't ask me why though.
	inline bool operator==(const Vector2& lhs, const Vector2& rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}
	inline bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !operator==(lhs, rhs); }

} }
#pragma once

#include<iostream>

namespace sudo { namespace math {

	class Vector2 {
	protected:
		float m_x, m_y;

	public:
		/* Default Constructor */
		Vector2() : m_x(0), m_y(0) { }

		/* Constructor (float) */
		Vector2(float a_x, float a_y) : m_x(a_x), m_y(a_y) { }

		/* Data Methods */
		void setX(float a_x);
		void setY(float a_y);

		float getX() const;
		float getY() const;

		inline static float GetMagnitude(const Vector2& vec) {
			// Return the magnitude of other
			return sqrt(pow(vec.getX(), 2) + pow(vec.getY(), 2));
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
		return (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY());
	}
	inline bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !operator==(lhs, rhs); }

} }
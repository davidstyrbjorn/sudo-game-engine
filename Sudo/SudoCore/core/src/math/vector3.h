#pragma once

#include<iostream>

namespace sudo { namespace math {

	class Vector3 {
	protected:
		float m_x, m_y, m_z;

	public:
		/* Default Constructor */
		Vector3() : m_x(0), m_y(0), m_z(0) { }

		/* Constructor (float) */
		Vector3(float a_x, float a_y, float a_z) : m_x(a_x), m_y(a_y), m_z(a_z) { }

		/* Data Methods */
		void setX(float a_x);
		void setY(float a_y);
		void setZ(float a_z);

		float getX() const;
		float getY() const;
		float getZ() const;

		inline static float GetMagnitude(const Vector3& vec) {
			// Return the magnitude of other
			return sqrt(pow(vec.getX(), 2) + pow(vec.getY(), 2) + pow(vec.getZ(), 2));
		}

		/* Operator Overloading Methods */
		Vector3 operator+(const Vector3 rhs);
		Vector3 operator-(const Vector3 rhs);
		Vector3 operator=(const Vector3 &rhs);
		Vector3 operator*(const float scalar);

		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);

		friend std::ostream& operator<<(std::ostream &os, const Vector3 &other);

		/* Static Methods */
		inline static Vector3 Right() { return Vector3(1, 0, 0); }
		inline static Vector3 Left()  { return Vector3(-1, 0, 0); }
		inline static Vector3 Up()    { return Vector3(0, -1, 0); }
		inline static Vector3 Down()  { return Vector3(0, 1, 0); }
	};

	inline bool operator==(const Vector3& lhs, const Vector3& rhs)
	{
		return (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ());
	}
	inline bool operator!=(const Vector3& lhs, const Vector3& rhs) { return !operator==(lhs, rhs); }

	}
}
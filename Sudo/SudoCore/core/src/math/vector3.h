#pragma once

#include<iostream>

namespace sudo { namespace math {

	struct Vector3 {
		float x, y, z;

		/* Default Constructor */
		Vector3() : x(0), y(0), z(0) { }

		/* Constructor (float) */
		Vector3(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z) { }

		/* Data Methods */
		void setX(float a_x);
		void setY(float a_y);
		void setZ(float a_z);

		inline static float GetMagnitude(const Vector3& vec) {
			// Return the magnitude of other
			return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
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
		return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
	}
	inline bool operator!=(const Vector3& lhs, const Vector3& rhs) { return !operator==(lhs, rhs); }

	}
}
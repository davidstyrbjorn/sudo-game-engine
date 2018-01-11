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
		const float getMagnitude() const;

		/* Operator Overloading Methods */
		/* Arithmetic Operators */
		Vector3 operator+(const Vector3 rhs);
		Vector3 operator-(const Vector3 rhs);
		Vector3 operator=(const Vector3 &rhs);
		Vector3 operator*(const float scalar);
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const float scalar);

		/* Comperative Operators */
		unsigned char operator>(const Vector3 &rhs);
		unsigned char operator<(const Vector3 &rhs);
		friend std::ostream& operator<<(std::ostream &os, const Vector3 &other);

		/* Static Methods */
		inline static Vector3 Right()		{ return Vector3(1, 0, 0); }
		inline static Vector3 Left()		{ return Vector3(-1, 0, 0); }
		inline static Vector3 Up()			{ return Vector3(0, -1, 0); }
		inline static Vector3 Down()		{ return Vector3(0, 1, 0); }
		inline static Vector3 Forward()		{ return Vector3(0, 0, 1); }
		inline static Vector3 Backwards()	{ return Vector3(0, 0, -1); }
		static Vector3 GetRandomVector(float a_minMagnitude, float a_maxMagnitude);
	};

	// I have to do this here for some reason, don't ask me why though.
	inline bool operator==(const Vector3& lhs, const Vector3& rhs)
	{
		return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
	}
	inline bool operator!=(const Vector3& lhs, const Vector3& rhs) { return !operator==(lhs, rhs); }

	}
}
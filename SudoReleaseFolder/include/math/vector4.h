#pragma once

#include<iostream>

namespace sudo {
	namespace math {

		struct Vector4 {
			float x, y, z, w;

			/* Default Constructor */
			Vector4() : x(0), y(0), z(0), w(0) { }

			/* Constructor (float) */
			Vector4(float a_x, float a_y, float a_z, float a_w) : x(a_x), y(a_y), z(a_z), w(a_w) { }

			/* Data Methods */
			void setX(float a_x);
			void setY(float a_y);
			void setZ(float a_z);
			void setW(float a_w);
			const float getMagnitude() const;

			/* Operator Overloading Methods */
			/* Arithmetic Operators */
			Vector4 operator+(const Vector4 rhs);
			Vector4 operator-(const Vector4 rhs);
			Vector4 operator=(const Vector4 &rhs);
			Vector4 operator*(const float scalar);
			Vector4& operator+=(const Vector4 &rhs);
			Vector4& operator-=(const Vector4 &rhs);
			Vector4& operator*=(const float scalar);

			/* Comperative Operators */
			unsigned char operator>(const Vector4 &rhs);
			unsigned char operator<(const Vector4 &rhs);
			friend std::ostream& operator<<(std::ostream &os, const Vector4 &other);
		};

		inline bool operator==(const Vector4& lhs, const Vector4& rhs) { return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w); }
		inline bool operator!=(const Vector4& lhs, const Vector4& rhs) { return !operator==(lhs, rhs); }

	}
}
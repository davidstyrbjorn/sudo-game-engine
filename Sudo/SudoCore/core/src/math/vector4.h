#pragma once

#include<iostream>

namespace sudo {
	namespace math {

		class Vector4 {
		private:
			float m_x, m_y, m_z, m_w;

		public:
			/* Default Constructor */
			Vector4() : m_x(0), m_y(0), m_z(0), m_w(0) { }

			/* Constructor (float) */
			Vector4(float a_x, float a_y, float a_z, float a_w) : m_x(a_x), m_y(a_y), m_z(a_z), m_w(a_w) { }

			/* Data Methods */
			void setX(float a_x);
			void setY(float a_y);
			void setZ(float a_z);
			void setW(float a_w);

			float getX() const;
			float getY() const;
			float getZ() const;
			float getW() const;

			inline static float GetMagnitude(const Vector4& vec) {
				// Return the magnitude of other
				return sqrt(pow(vec.getX(), 2) + pow(vec.getY(), 2) + pow(vec.getZ(), 2) + pow(vec.getW(), 2));
			}

			/* Operator Overloading Methods */
			Vector4 operator+(const Vector4 rhs);
			Vector4 operator-(const Vector4 rhs);
			Vector4 operator=(const Vector4 &rhs);
			Vector4 operator*(const float scalar);

			Vector4& operator+=(const Vector4& rhs);
			Vector4& operator-=(const Vector4& rhs);

			friend std::ostream& operator<<(std::ostream &os, const Vector4 &other);
		};

		inline bool operator==(const Vector4& lhs, const Vector4& rhs) { return (lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ() && lhs.getW() == rhs.getW()); }
		inline bool operator!=(const Vector4& lhs, const Vector4& rhs) { return !operator==(lhs, rhs); }

	}
}

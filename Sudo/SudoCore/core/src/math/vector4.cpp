#include "vector4.h"

namespace sudo {
	namespace math {

		// Vector normal methods
		void Vector4::setX(float a_x)
		{
			this->x = a_x;
		}

		void Vector4::setY(float a_y)
		{
			this->y = a_y;
		}

		void Vector4::setZ(float a_z)
		{
			this->z = a_z;
		}

		void Vector4::setW(float a_w) 
		{
			this->w = a_w;
		}

		/* Operator overloaded functions */
		Vector4 Vector4::operator+(const Vector4 rhs)
		{
			return Vector4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
		}

		Vector4 Vector4::operator-(const Vector4 rhs)
		{
			return Vector4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w-rhs.w);
		}

		Vector4 Vector4::operator=(const Vector4 &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->w = rhs.w;
			return *this;
		}

		Vector4 Vector4::operator*(const float scalar)
		{
			return Vector4(this->x*scalar, this->y*scalar, this->z*scalar, this->w*scalar);
		}

		Vector4 & Vector4::operator+=(const Vector4 & rhs)
		{
			this->x = this->x + rhs.x;
			this->y = this->y + rhs.y;
			this->z = this->z + rhs.z;
			this->w = this->w + rhs.w;
			return *this;
		}

		Vector4 & Vector4::operator-=(const Vector4 & rhs)
		{
			this->x = this->x - rhs.x;
			this->y = this->y - rhs.y;
			this->z = this->z - rhs.z;
			this->w = this->w - rhs.w;
			return *this;
		}

		std::ostream & math::operator<<(std::ostream & os, const Vector4 & other)
		{
			os << "(" << other.x << ", " << other.y << ", " << other.z << ", " << other.w << ")";
			return os;
		}
	}
}
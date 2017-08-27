#include "vector4.h"

namespace sudo {
	namespace math {

		// Vector normal methods
		void Vector4::setX(float a_x)
		{
			this->m_x = a_x;
		}

		void Vector4::setY(float a_y)
		{
			this->m_y = a_y;
		}

		void Vector4::setZ(float a_z)
		{
			this->m_z = a_z;
		}

		void Vector4::setW(float a_w) 
		{
			this->m_w = a_w;
		}

		float Vector4::getX() const
		{
			return m_x;
		}

		float Vector4::getY() const
		{
			return m_y;
		}

		float Vector4::getZ() const
		{
			return m_z;
		}

		float Vector4::getW() const
		{
			return m_w;
		}

		/* Operator overloaded functions */
		Vector4 Vector4::operator+(const Vector4 rhs)
		{
			return Vector4(this->m_x + rhs.m_x, this->m_y + rhs.m_y, this->m_z + rhs.m_z, this->m_w + rhs.m_w);
		}

		Vector4 Vector4::operator-(const Vector4 rhs)
		{
			return Vector4(this->m_x - rhs.m_x, this->m_y - rhs.m_y, this->m_z - rhs.m_z, this->m_w-rhs.m_w);
		}

		Vector4 Vector4::operator=(const Vector4 &rhs)
		{
			this->m_x = rhs.m_x;
			this->m_y = rhs.m_y;
			this->m_z = rhs.m_z;
			this->m_w = rhs.m_w;
			return *this;
		}

		Vector4 Vector4::operator*(const float scalar)
		{
			return Vector4(this->m_x*scalar, this->m_y*scalar, this->m_z*scalar, this->m_w*scalar);
		}

		Vector4 & Vector4::operator+=(const Vector4 & rhs)
		{
			this->m_x = this->m_x + rhs.m_x;
			this->m_y = this->m_y + rhs.m_y;
			this->m_z = this->m_z + rhs.m_z;
			this->m_w = this->m_w + rhs.m_w;
			return *this;
		}

		Vector4 & Vector4::operator-=(const Vector4 & rhs)
		{
			this->m_x = this->m_x - rhs.m_x;
			this->m_y = this->m_y - rhs.m_y;
			this->m_z = this->m_z - rhs.m_z;
			this->m_w = this->m_w - rhs.m_w;
			return *this;
		}

		std::ostream & math::operator<<(std::ostream & os, const Vector4 & other)
		{
			os << "(" << other.m_x << ", " << other.m_y << ", " << other.m_z << ", " << other.m_w << ")";
			return os;
		}
	}
}
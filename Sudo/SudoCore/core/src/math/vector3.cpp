#include "vector3.h"

namespace sudo {
	namespace math {

		// Vector normal methods
		void Vector3::setX(float a_x)
		{
			this->m_x = a_x;
		}

		void Vector3::setY(float a_y)
		{
			this->m_y = a_y;
		}

		void Vector3::setZ(float a_z) 
		{
			this->m_z = a_z;
		}

		float Vector3::getX() const
		{
			return m_x;
		}

		float Vector3::getY() const
		{
			return m_y;
		}

		float Vector3::getZ() const
		{
			return m_z;
		}

		/* Operator overloaded functions */
		Vector3 Vector3::operator+(const Vector3 rhs)
		{
			return Vector3(this->m_x + rhs.m_x, this->m_y + rhs.m_y, this->m_z + rhs.m_z);
		}

		Vector3 Vector3::operator-(const Vector3 rhs)
		{
			return Vector3(this->m_x - rhs.m_x, this->m_y - rhs.m_y, this->m_z - rhs.m_z);
		}

		Vector3 Vector3::operator=(const Vector3 &rhs)
		{
			this->m_x = rhs.m_x;
			this->m_y = rhs.m_y;
			this->m_z = rhs.m_z;
			return *this;
		}

		Vector3 Vector3::operator*(const float scalar)
		{
			return Vector3(this->m_x*scalar,this->m_y*scalar, this->m_z*scalar);
		}

		Vector3 & Vector3::operator+=(const Vector3 & rhs)
		{
			this->m_x = this->m_x + rhs.m_x;
			this->m_y = this->m_y + rhs.m_y;
			this->m_z = this->m_z + rhs.m_z;
			return *this;
		}

		Vector3 & Vector3::operator-=(const Vector3 & rhs)
		{
			this->m_x = this->m_x - rhs.m_x;
			this->m_y = this->m_y - rhs.m_y;
			this->m_z = this->m_z - rhs.m_z;
			return *this;
		}

		std::ostream & math::operator<<(std::ostream & os, const Vector3 & other)
		{
			os << "(" << other.m_x << ", " << other.m_y << ", " << other.m_z << ")";
			return os;
		}
	}
}
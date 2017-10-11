#include "vector3.h"

namespace sudo {
	namespace math {

		void Vector3::setX(float a_x)
		{
			this->x = a_x;
		}

		void Vector3::setY(float a_y)
		{
			this->y = a_y;
		}

		void Vector3::setZ(float a_z) 
		{
			this->z = a_z;
		}

		const float Vector3::getMagnitude() const
		{
			return sqrt(powf(this->x, 2) + powf(this->y, 2) + powf(this->z, 2));
		}

		Vector3 Vector3::operator+(const Vector3 rhs)
		{
			return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
		}

		Vector3 Vector3::operator-(const Vector3 rhs)
		{
			return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
		}

		Vector3 Vector3::operator=(const Vector3 &rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			return *this;
		}

		Vector3 Vector3::operator*(const float scalar)
		{
			return Vector3(this->x*scalar,this->y*scalar, this->z*scalar);
		}

		Vector3 & Vector3::operator+=(const Vector3 & rhs)
		{
			this->x = this->x + rhs.x;
			this->y = this->y + rhs.y;
			this->z = this->z + rhs.z;
			return *this;
		}

		Vector3 & Vector3::operator-=(const Vector3 & rhs)
		{
			this->x = this->x - rhs.x;
			this->y = this->y - rhs.y;
			this->z = this->z - rhs.z;
			return *this;
		}

		Vector3 & Vector3::operator*=(const float scalar)
		{
			return Vector3(this->x*scalar, this->y*scalar, this->z*scalar);
		}

		unsigned char Vector3::operator>(const Vector3 & rhs)
		{
			return this->getMagnitude() > rhs.getMagnitude();
		}

		unsigned char Vector3::operator<(const Vector3 & rhs)
		{
			return !operator>(rhs);
		}

		std::ostream & math::operator<<(std::ostream & os, const Vector3 & other)
		{
			os << "(" << other.x << ", " << other.y << ", " << other.z << ")";
			return os;
		}
	}
}
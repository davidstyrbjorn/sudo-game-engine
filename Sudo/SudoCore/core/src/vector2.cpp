#include "../include/math/vector2.h"
#include"../include/utility/sudo_random.h"

namespace sudo { namespace math {

	void Vector2::setX(float a_x)
	{
		this->x = a_x;
	}

	void Vector2::setY(float a_y)
	{
		this->y = a_y;
	}

	const float Vector2::getMagnitude() const
	{
		return sqrt(powf(this->x, 2) + powf(this->y, 2));
	}

	Vector2 Vector2::operator+(const Vector2 rhs)
	{
		return Vector2(this->x+rhs.x,this->y+rhs.y);
	}

	Vector2 Vector2::operator-(const Vector2 rhs)
	{
		return Vector2(this->x-rhs.x,this->y-rhs.y);
	}

	Vector2 Vector2::operator*(const float scalar)
	{
		return Vector2(this->x * scalar, this->y * scalar);
	}

	unsigned char Vector2::operator>(const Vector2 & rhs)
	{
		return this->getMagnitude() > rhs.getMagnitude();
	}

	unsigned char Vector2::operator<(const Vector2 & rhs)
	{
		return !operator>(rhs);
	}

	Vector2 Vector2::GetRandomVector(float a_minMagnitude, float a_maxMagnitude)
	{
		Vector2 temp(utility::SudoRandomNumber::GetRandomFloatingPoint(a_minMagnitude, a_maxMagnitude), utility::SudoRandomNumber::GetRandomFloatingPoint(a_minMagnitude, a_maxMagnitude));
		return temp;
	}

	Vector2 Vector2::operator=(const Vector2 &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}

	Vector2 & Vector2::operator+=(const Vector2 & rhs)
	{
		this->x = this->x + rhs.x;
		this->y = this->y + rhs.y;
		return *this;
	}

	Vector2 & Vector2::operator-=(const Vector2 & rhs)
	{
		this->x = this->x - rhs.x;
		this->y = this->y - rhs.y;
		return *this;
	}

	Vector2 & Vector2::operator*=(const float scalar)
	{
		return Vector2(this->x*scalar, this->y*scalar);
	}

	std::ostream & math::operator<<(std::ostream & os, const Vector2 & other)
	{
		os << "(" << other.x << ", " << other.y << ")";
		return os;
	}
}
}
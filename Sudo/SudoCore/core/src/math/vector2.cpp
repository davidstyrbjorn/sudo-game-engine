#include "vector2.h"

namespace sudo { namespace math {

	// Vector normal methods
	void Vector2::setX(float a_x)
	{
		this->x = a_x;
	}

	void Vector2::setY(float a_y)
	{
		this->y = a_y;
	}

	/* Operator overloaded functions */
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
		if (GetMagnitude(*this) > GetMagnitude(rhs))
			return true;
		return false;
	}

	unsigned char Vector2::operator<(const Vector2 & rhs)
	{
		if (GetMagnitude(*this) < GetMagnitude(rhs))
			return true;
		return false;
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

	std::ostream & math::operator<<(std::ostream & os, const Vector2 & other)
	{
		os << "(" << other.x << ", " << other.y << ")";
		return os;
	}
}
}
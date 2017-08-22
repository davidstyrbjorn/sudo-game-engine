#include "vector2.h"

namespace sudo { namespace math {

	// Vector normal methods
	void Vector2::setX(float a_x)
	{
		this->m_x = a_x;
	}

	void Vector2::setY(float a_y)
	{
		this->m_y = a_y;
	}

	float Vector2::getX() const
	{
		return m_x;
	}

	float Vector2::getY() const
	{
		return m_y;
	}

	/* Operator overloaded functions */
	Vector2 Vector2::operator+(const Vector2 rhs)
	{
		return Vector2(this->m_x+rhs.m_x,this->m_y+rhs.m_y);
	}

	Vector2 Vector2::operator-(const Vector2 rhs)
	{
		return Vector2(this->m_x-rhs.m_x,this->m_y-rhs.m_y);
	}

	Vector2 Vector2::operator*(const float scalar)
	{
		return Vector2(this->m_x*scalar, this->m_y*scalar);
	}

	Vector2 Vector2::operator=(const Vector2 &rhs)
	{
		this->m_x = rhs.m_x;
		this->m_y = rhs.m_y;
		return *this;
	}

	Vector2 & Vector2::operator+=(const Vector2 & rhs)
	{
		this->m_x = this->m_x + rhs.m_x;
		this->m_y = this->m_y + rhs.m_y;
		return *this;
	}

	Vector2 & Vector2::operator-=(const Vector2 & rhs)
	{
		this->m_x = this->m_x - rhs.m_x;
		this->m_y = this->m_y - rhs.m_y;
		return *this;
	}

	std::ostream & math::operator<<(std::ostream & os, const Vector2 & other)
	{
		os << "(" << other.m_x << ", " << other.m_y << ")";
		return os;
	}
}
}
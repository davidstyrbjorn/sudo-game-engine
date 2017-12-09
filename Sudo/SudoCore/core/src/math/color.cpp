#include "color.h"

namespace sudo {
	namespace math {

		Color Color::operator+(const Color rhs)
		{
			return Color(this->r + rhs.r, this->g + rhs.g, this->b + rhs.b, this->a + rhs.a);
		}

		Color Color::operator-(const Color rhs)
		{
			return Color(this->r - rhs.r, this->g - rhs.g, this->b - rhs.b, this->a - rhs.a);
		}

		Color Color::operator/(const float rhs) 
		{
			return Color(this->r / rhs, this->g / rhs, this->b / rhs, this->a / rhs);
		}

		Color Color::operator=(const Color &rhs)
		{
			this->r = rhs.r;
			this->g = rhs.g;
			this->b = rhs.b;
			this->a = rhs.a;
			return *this;
		}

		Color Color::operator*(const float scalar)
		{
			return Color(this->r*scalar, this->g*scalar, this->b*scalar, this->a*scalar);
		}

		Color & Color::operator+=(const Color & rhs)
		{
			this->r = this->r + rhs.r;
			this->g = this->g + rhs.g;
			this->b = this->b + rhs.b;
			this->a = this->a + rhs.a;
			return *this;
		}

		Color & Color::operator-=(const Color & rhs)
		{
			this->r = this->r - rhs.r;
			this->g = this->g - rhs.g;
			this->b = this->b - rhs.b;
			this->a = this->a - rhs.a;
			return *this;
		}

		Color & Color::operator*=(const float scalar)
		{
			return Color(this->r*scalar, this->g*scalar, this->b*scalar, this->a*scalar);
		}

		std::ostream & math::operator<<(std::ostream & os, const Color & other)
		{
			os << "(" << other.r << ", " << other.g << ", " << other.b << ", " << other.a << ")";
			return os;
		}
	}
}
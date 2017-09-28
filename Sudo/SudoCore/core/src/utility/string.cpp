#include "string.h"

namespace sudo { namespace utility {

	String String::operator=(const char * rhs)
	{
		String temp;
		temp.assign((char*)rhs);
		return temp;
	}

	String String::operator+=(const char * rhs)
	{
		return String(this->m_characterData+rhs);
	}

	String String::operator+=(const String & rhs)
	{
		return String(get_data() + rhs.get_data());
	}

	void String::assign(char * a_characterData)
	{
		m_characterData = a_characterData;
	}

	constexpr char * String::get_data()
	{
		return m_characterData;
	}

	char String::at(int a_index) const
	{
		for (int i = 0; i < length(); i++) {
			if (i == a_index) {
				return m_characterData[i];
			}
		}

		return ' ';
	}

	uint String::length() const
	{
		return strlen(m_characterData);
	}

	std::ostream & utility::operator<<(std::ostream & os, String & other)
	{
		os << other.get_data();
		return os;
	}

} }
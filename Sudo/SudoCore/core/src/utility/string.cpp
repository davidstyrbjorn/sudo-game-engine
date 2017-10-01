#include "string.h"

namespace sudo { namespace utility {

	SudoString SudoString::operator=(const char * rhs)
	{
		SudoString temp;
		temp.assign((char*)rhs);
		return temp;
	}

	SudoString SudoString::operator+(const char * rhs)
	{
		SudoString newString(this->m_characterData);

		// Loo through rhs and add all of it's characters to the newString
		for (int i = 0; i < strlen(rhs); i++) {
			newString.m_characterData += rhs[i];
		}

		return newString;
	}

	SudoString SudoString::operator+(const SudoString &rhs)
	{
		SudoString newString(this->m_characterData);

		// Loop through rhs and add all of it's characters to the newString
		for (int i = 0; i < rhs.length(); i++) {
			newString.m_characterData += rhs.at(i);
		}

		return newString;
	}

	void SudoString::assign(char * a_characterData)
	{
		m_characterData = a_characterData;
	}

	char * SudoString::get_data()
	{
		return m_characterData;
	}

	char SudoString::at(int a_index) const
	{
		for (int i = 0; i < length(); i++) {
			if (i == a_index) {
				return m_characterData[i];
			}
		}

		return ' ';
	}

	uint SudoString::length() const
	{
		return strlen(m_characterData);
	}

	std::ostream & utility::operator<<(std::ostream & os, SudoString & other)
	{
		os << other.get_data();
		return os;
	}

} }
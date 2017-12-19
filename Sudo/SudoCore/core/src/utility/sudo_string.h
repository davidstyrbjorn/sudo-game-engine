#pragma once

#include<iostream>
#include"../../definitions.h"

namespace sudo { namespace utility { 

	class SudoString {
	private:
		char* m_characterData;

	public:
		/* Constructors */
		SudoString() { }
		SudoString(const char* a_characterData) : m_characterData((char*)a_characterData) { }

		/* Operator Overloading */
		SudoString operator=(const char* rhs);
		inline bool operator==(SudoString& rhs)
		{
			return (rhs.get_data() == this->get_data());
		}
		inline bool operator==(const char* rhs) 
		{
			return (rhs == this->get_data());
		}
		inline bool operator!=(SudoString& rhs)
		{
			return !operator==(rhs);
		}
		friend std::ostream& operator<<(std::ostream &os, SudoString &other);

		SudoString operator+(const char* rhs);
		SudoString operator+(const SudoString &rhs);
		SudoString operator+(const std::string &rhs);

		/* Public Member Functions */

		// brief\ Sets the actual string using char*
		void assign(char* a_characterData);
		
		// brief\ returns the character data
		char* get_data();

		// brief\ returns character at in-argument index
		char at(int a_index) const;

		// brief\ returns the length of the string
		uint length() const;
	};

}} 
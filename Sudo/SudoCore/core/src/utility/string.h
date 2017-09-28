#pragma once

#include<iostream>
#include"../../definitions.h"

namespace sudo { namespace utility { 

	class String {
	private:
		char* m_characterData;

	public:
		/* Constructors */
		String() { }
		String(const char* a_characterData) : m_characterData((char*)a_characterData) { }

		/* Operator Overloading */
		String operator=(const char* rhs);
		inline bool operator==(String& rhs)
		{
			return (rhs.get_data() == this->get_data());
		}
		inline bool operator!=(String& rhs)
		{
			return !operator==(rhs);
		}
		friend std::ostream& operator<<(std::ostream &os, String &other);

		String operator+=(const char* rhs);
		String operator+=(const String &rhs);

		/* Public Member Functions */

		// brief\ Sets the actual string using char*
		void assign(char* a_characterData);
		
		// brief\ returns the character data
		constexpr char* get_data();

		// brief\ returns character at in-argument index
		char at(int a_index) const;

		// brief\ returns the length of the string
		uint length() const;
	};

}} 
#pragma once

#include"../../sudo.h"
#include<fstream>

namespace sudo { namespace utility {

	static std::string GetFileContent(const char* a_fileName) {

		std::ifstream file(a_fileName);
		std::string content((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));

		if (!file.is_open()) {
			std::cout << "Could not open " << a_fileName << std::endl;
		}

		return content;
	}
} }
#pragma once

#include"../../sudo.h"
#include<fstream>

#include"../debug.h"

namespace sudo { namespace utility {

	static std::string GetFileContent(const char* a_fileName) {

		std::ifstream file(a_fileName);
		std::string content((std::istreambuf_iterator<char>(file)),
			(std::istreambuf_iterator<char>()));

		if (!file.is_open()) {
			DEBUG::getInstance()->printMessage(a_fileName, LogType::Error);
		}

		return content;
	}
} }
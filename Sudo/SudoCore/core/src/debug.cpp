#include "debug.h"

#include<iostream>
#include<fstream>

#include<chrono>
#include<ctime>

#include<string>

namespace sudo {

	void DEBUG::logMessage(const char * a_message, LogType a_type)
	{
		std::ofstream file("sudo_debug.txt", std::ios::app, std::ios::_Openprot);
		std::string finalMessage;

		// Get the current system time
		std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
		std::time_t _time = std::chrono::system_clock::to_time_t(time);
		std::string timeText = std::ctime(&_time);
		timeText = "[" + timeText.substr(0, timeText.length() - 9) + "]";

		switch (a_type) 
		{
		case LogType::Debug:
			finalMessage = timeText + "(DEBUG: " + a_message + ")";
			break;
		case LogType::Error:
			finalMessage = timeText + "(ERROR: " + a_message + ")";
			break;
		case LogType::Fatal:
			finalMessage = timeText + "(FATAL: " + a_message + ")";
			break;
		case LogType::Warning:
			finalMessage = timeText + "(WARNING: " + a_message + ")";
			break;
		default:
			finalMessage = timeText + "(Something went wrong inside debug.cpp->logMessage()" + ")";
			break;
		}

		/* Deliver the log message to the file then close it */
		file << finalMessage << std::endl;
		file.close();
	}

	void DEBUG::printMessage(const char * a_message, LogType a_type) 
	{
		std::string finalMessage;

		// Get the current system time
		std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
		std::time_t _time = std::chrono::system_clock::to_time_t(time);
		std::string timeText = std::ctime(&_time);
		timeText = "[" + timeText.substr(0, timeText.length() - 9) + "]";

		switch (a_type)
		{
		case LogType::Debug:
			finalMessage = timeText + "(DEBUG: " + a_message + ")";
			break;
		case LogType::Error:
			finalMessage = timeText + "(ERROR: " + a_message + ")";
			break;
		case LogType::Fatal:
			finalMessage = timeText + "(FATAL: " + a_message + ")";
			break;
		case LogType::Warning:
			finalMessage = timeText + "(WARNING: " + a_message + ")";
			break;
		default:
			finalMessage = timeText + "(Something went wrong inside debug.cpp->logMessage()" + ")";
			break;
		}

		/* Deliver the log message to the file then close it */
		std::cout << finalMessage << std::endl;
	}

}
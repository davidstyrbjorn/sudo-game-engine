#pragma once

#include"utility\string.h"

namespace sudo {

	enum LogType {
		Debug,
		Warning,
		Error,
		Fatal
	};

	class DEBUG {
	public:
		static DEBUG* getInstance(){
			static DEBUG instance;
			return &instance;
		}

		/* Logs message to a text file used only for bad breaks */
		void logMessage(const char* a_message, LogType a_type = LogType::Debug);

		/* Prints the error message to the console */
		void printMessage(const char* a_message, LogType a_type = LogType::Debug);

	private:
		DEBUG() { }
	};
}
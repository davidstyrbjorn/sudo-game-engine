#pragma once

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

		void logMessage(const char* a_message, LogType a_type = LogType::Debug);
		void printMessage(const char* a_message, LogType a_type = LogType::Debug);

	private:
		DEBUG() { }
	};

}
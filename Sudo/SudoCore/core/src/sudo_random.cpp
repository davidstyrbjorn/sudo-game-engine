#include"../include/utility/sudo_random.h"

namespace sudo { namespace utility {

	// I don't understand why I cant do this inside the .h file but this makes it compile so whatever
	std::random_device SudoRandomNumber::m_randomDevice;
	
} }
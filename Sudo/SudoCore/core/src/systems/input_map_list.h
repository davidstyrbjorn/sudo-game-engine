#pragma once

#include"input_system.h"

namespace sudo { namespace system {

	void InputSystem::populateKeyList() 
	{
		keyList[65] = Key(0, "a");
		keyList[66] = Key(0, "b");
		keyList[67] = Key(0, "c");
		keyList[68] = Key(0, "d");
		keyList[69] = Key(0, "e");
		keyList[70] = Key(0, "f");
	}

} }
#pragma once

namespace sudo { namespace sudo_system {

	/* Base Class for all system classes */
	class SudoSystem {
	public:
		/* Virtual Destructor */
		virtual ~SudoSystem() { }

		/* Enables said system, pure virtual */
		virtual void Enable() = 0;

		/* Disable said system, pure virtual */
		virtual void Disable() = 0;

		/* Cleans up the necessary thing to prevent memory leaks when quitting */
		virtual void CleanUp() = 0;
	};

} }
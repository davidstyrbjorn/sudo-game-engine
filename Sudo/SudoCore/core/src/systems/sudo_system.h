#pragma once

namespace sudo { namespace {

	/* Base Class for all system classes */
	class SudoSystem {
	public:
		/* Virtual Destructor */
		virtual ~SudoSystem() { }

		/* Enables said system */
		virtual void Enable() = 0;

		/* Disable said system */
		virtual void Disable() = 0;
	};

} }
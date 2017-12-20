#pragma once

namespace sudo { namespace graphics {

	// Shared methods for every class that renders prmitives to the screen
	// Mainly used for my sanity in the main loop

	class RendererBase {
	public:
		virtual void Begin() = 0;
		virtual void Flush() = 0;
		virtual void End() = 0;
	};

} }
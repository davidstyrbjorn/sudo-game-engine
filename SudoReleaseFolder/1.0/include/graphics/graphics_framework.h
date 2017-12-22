#pragma once

namespace sudo { namespace graphics {

	class GraphicsFramework {
	public:
		virtual void clear() = 0;
		virtual void display() = 0;
		virtual void close() = 0;
		virtual bool is_open() = 0;
	};
} }
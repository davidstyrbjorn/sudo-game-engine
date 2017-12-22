#pragma once

typedef unsigned int uint;

namespace sudo { namespace graphics { 

	class VertexArrayBuffer {
	private:
		uint m_id;

	public:
		/* Constructor */
		VertexArrayBuffer();

		/* Destructor */
		~VertexArrayBuffer();

		/* Binds the vertex array tied to id */
		void bind() const;

		/* --||-- unbinds --||-- */
		void unbind() const;
	};

} } 
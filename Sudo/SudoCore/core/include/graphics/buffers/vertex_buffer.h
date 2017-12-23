#pragma once

#include"../../definitions.h"

namespace sudo {
	namespace math {
		class Vector4;
	}
}

namespace sudo { namespace graphics { 

	class QuadVertexData;

	class VertexBuffer
	{
	private:
		unsigned int m_vbo;
		SudoBufferType m_type;

	public:
		/* Constructor */
		VertexBuffer(QuadVertexData* a_data, uint a_size);

		/* Destructor */
		virtual ~VertexBuffer();

		/* Binds the vertex buffer */
		void bind() const;

		/* Unbinds the vertex buffer */
		void unbind() const;

		void dataModified(float a_data[], uint a_size);
		void dataModified(const math::Vector4 &a_color);
	};

} }
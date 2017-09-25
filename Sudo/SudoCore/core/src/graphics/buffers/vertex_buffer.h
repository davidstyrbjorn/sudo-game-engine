#pragma once

#include"../../../definitions.h"

namespace sudo { namespace graphics { 

	class VertexBuffer
	{
	private:
		unsigned int m_vbo;
		SudoBufferType m_type;

	public:
		/* Constructor */
		VertexBuffer(float a_data[], uint a_size, SudoBufferType a_type);

		/* Destructor */
		virtual ~VertexBuffer();

		/* Binds the vertex buffer */
		void bind() const;

		/* Unbinds the vertex buffer */
		void unbind() const;

		void dataModified(float a_data[], uint a_size);
	};

} }
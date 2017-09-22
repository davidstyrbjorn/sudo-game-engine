#pragma once

#include"../../../definitions.h"

namespace sudo { namespace graphics { 

	class VertexBuffer
	{
	private:
		unsigned int m_vbo;

	public:
		/* Constructor */
		VertexBuffer(float a_data[], uint a_size, SudoBufferType a_type);

		/* Destructor */
		virtual ~VertexBuffer();

		/* Binds the vertex buffer */
		void bind() const;

		/* Unbinds the vertex buffer */
		void unbind() const;

		/* Data inside the buffer was modified */
		void DataModified(float a_data[], uint a_size, SudoBufferType a_type);
	};

} }
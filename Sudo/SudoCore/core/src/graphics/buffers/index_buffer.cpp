#include"index_buffer.h"

#include"../../../gl_include.h"

namespace sudo { namespace graphics { 

	IndexBuffer::IndexBuffer()
	{
		
	}

	IndexBuffer::IndexBuffer(unsigned int *a_indices, uint a_size) 
	{
		// Create and bind the buffer
		glGenBuffers(1, &m_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);

		// Fill the buffer with the indicies data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_size, a_indices, GL_STATIC_DRAW);
	}

	void IndexBuffer::setData(unsigned int *a_indicies, uint a_size)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_size, a_indicies, GL_STATIC_DRAW);
	}

	void IndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer);
	}

	void IndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


} }
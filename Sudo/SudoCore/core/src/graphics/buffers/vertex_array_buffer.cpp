#include"vertex_array_buffer.h"
#include"../../../gl_include.h"

namespace sudo { namespace graphics { 

	VertexArrayBuffer::VertexArrayBuffer() 
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArrayBuffer::~VertexArrayBuffer()
	{
		glDeleteBuffers(1, &m_id);
	}

	void VertexArrayBuffer::bind() const 
	{
		glBindVertexArray(m_id);
	}

	void VertexArrayBuffer::unbind() const
	{
		glBindVertexArray(0);
	}

}} 
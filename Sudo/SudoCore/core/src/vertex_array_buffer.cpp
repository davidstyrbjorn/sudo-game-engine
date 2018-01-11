#include"../include/graphics/buffers/vertex_array_buffer.h"

#define GLEW_STATIC
#include"GL\glew.h"

namespace sudo { namespace graphics { 

	VertexArrayBuffer::VertexArrayBuffer() 
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArrayBuffer::~VertexArrayBuffer()
	{
		glDeleteVertexArrays(1, &m_id);
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
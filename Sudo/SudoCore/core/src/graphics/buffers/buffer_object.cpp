#include"buffer_object.h"

namespace sudo { namespace graphics { 

	BufferObject::~BufferObject()
	{
		glDeleteBuffers(1, &m_id);
	}

	BufferObject::BufferObject() 
	{

	}

	void BufferObject::bind() const
	{
		glBindBuffer(m_bufferType, m_id);
	}

	void BufferObject::unbind() const
	{
		glBindBuffer(m_bufferType, 0);
	}

} }
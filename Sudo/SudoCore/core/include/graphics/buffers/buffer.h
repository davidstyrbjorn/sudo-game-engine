#pragma once

#include"../../definitions.h"

namespace sudo { namespace graphics { 

	class Buffer {
	private:
		GLuint m_id;
		GLenum m_type;

	public:
		/* Constructor */
		Buffer();

		/* Desctructor */
		~Buffer();

		/* Init the buffer */
		Buffer(GLenum a_type, unsigned a_data[], unsigned int a_size) : m_type(a_type)
		{
			m_type = a_type;

			/*
			glGenBuffers(1, &m_id);
			glBindBuffer(a_type, m_id);
			glBufferData(a_type, a_size, a_data, GL_STATIC_DRAW);
			*/
		}

		/* Binds the buffer */
		void bind() const;

		/* Unbinds the bound buffer */
		void unbind() const;
	};

} }  
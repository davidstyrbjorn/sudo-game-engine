#include "../include/graphics/buffers/vertex_buffer.h"

#define GLEW_STATIC
#include"GL\glew.h"

#include<iostream>

#include<cassert>
#include<cstdint>

#include"../include/graphics/renderable2d.h"

#include"../include/math/vector4.h"

namespace sudo { namespace graphics { 

	VertexBuffer::VertexBuffer(QuadVertexData* a_data, uint a_size)
	{
		// Create and bind buffer
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		
		// Structure the buffer layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertexData), nullptr); // Vertex position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertexData), reinterpret_cast<void*>(offsetof(QuadVertexData, color))); // Vertex color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertexData), reinterpret_cast<void*>(offsetof(QuadVertexData, uv)));
		glEnableVertexAttribArray(2);
		
		glBufferData(GL_ARRAY_BUFFER, a_size, a_data, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_vbo);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::dataModified(float a_data[], uint a_size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//glBufferData(GL_ARRAY_BUFFER, a_size, a_data, GL_STATIC_DRAW);
	}

	void VertexBuffer::dataModified(const math::Vector4 &a_color)
	{
		float color[] = {
			a_color.x,a_color.y,a_color.z,a_color.w,
		};
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(QuadVertexData) * 0) + (3 * sizeof(float)), 4 * sizeof(float), color);
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(QuadVertexData) * 1) + (3 * sizeof(float)), 4 * sizeof(float), color);
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(QuadVertexData) * 2) + (3 * sizeof(float)), 4 * sizeof(float), color);
		glBufferSubData(GL_ARRAY_BUFFER, (sizeof(QuadVertexData) * 3) + (3 * sizeof(float)), 4 * sizeof(float), color);
	}

}} 
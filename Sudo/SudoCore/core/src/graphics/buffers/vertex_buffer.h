#pragma once

#include"../../../definitions.h"

#include"../renderable2d.h"

namespace sudo { namespace graphics { 

	class VertexBuffer
	{
	private:
		unsigned int m_vbo;
		SudoBufferType m_type;

	public:
		/* Constructor */
		VertexBuffer(VertexData* a_data, uint a_size);

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
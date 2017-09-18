#pragma once

namespace sudo { namespace graphics { 

	class VertexBuffer
	{
	private:
		unsigned int m_vbo;

	public:
		/* Constructor */
		VertexBuffer(float a_data[24]);

		/* Destructor */
		virtual ~VertexBuffer();

		/* Binds the vertex buffer */
		void bind() const;

		/* Unbinds the vertex buffer */
		void unbind() const;
	};

} }
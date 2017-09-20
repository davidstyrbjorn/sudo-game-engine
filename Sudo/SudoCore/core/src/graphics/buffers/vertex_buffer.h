#pragma once

namespace sudo { namespace graphics { 

	enum SudoBuferType {
		VERTEX_ONLY,
		VERTEX_COLOR,
		VERTEX_COLOR_TEXTURE
	};

	class VertexBuffer
	{
	private:
		unsigned int m_vbo;

	public:
		/* Constructor */
		VertexBuffer(float a_data[], unsigned int a_size, SudoBuferType a_type);

		/* Destructor */
		virtual ~VertexBuffer();

		/* Binds the vertex buffer */
		void bind() const;

		/* Unbinds the vertex buffer */
		void unbind() const;
	};

} }